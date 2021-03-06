/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "followupreminderagent.h"
#include "followupremindermanager.h"
#include "followupreminderutil.h"
#include "followupreminderadaptor.h"
#include "followupreminderagentsettings.h"
#include "followupreminderinfo.h"

#include <KMime/Message>

#include <AkonadiCore/ChangeRecorder>
#include <AkonadiCore/ItemFetchScope>
#include <QDBusConnection>

#include <Kdelibs4ConfigMigrator>
#include <AkonadiCore/Session>
#include <AkonadiCore/CollectionFetchScope>
#include <AkonadiCore/ServerManager>

#include "followupreminderagent_debug.h"
#include <QTimer>

FollowUpReminderAgent::FollowUpReminderAgent(const QString &id)
    : Akonadi::AgentBase(id)
{
    Kdelibs4ConfigMigrator migrate(QStringLiteral("followupreminderagent"));
    migrate.setConfigFiles(QStringList() << QStringLiteral("akonadi_followupreminder_agentrc") << QStringLiteral("akonadi_followupreminder_agent.notifyrc"));
    migrate.migrate();

    new FollowUpReminderAgentAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/FollowUpReminder"), this, QDBusConnection::ExportAdaptors);
    const QString service = Akonadi::ServerManager::self()->agentServiceName(Akonadi::ServerManager::Agent, QStringLiteral("akonadi_followupreminder_agent"));
    QDBusConnection::sessionBus().registerService(service);
    mManager = new FollowUpReminderManager(this);
    setNeedsNetwork(true);

    changeRecorder()->setMimeTypeMonitored(KMime::Message::mimeType());
    changeRecorder()->itemFetchScope().setCacheOnly(true);
    changeRecorder()->itemFetchScope().setFetchModificationTime(false);
    changeRecorder()->fetchCollection(true);
    changeRecorder()->setChangeRecordingEnabled(false);
    changeRecorder()->ignoreSession(Akonadi::Session::defaultSession());
    changeRecorder()->collectionFetchScope().setAncestorRetrieval(Akonadi::CollectionFetchScope::All);
    changeRecorder()->setCollectionMonitored(Akonadi::Collection::root(), true);

    if (FollowUpReminderAgentSettings::enabled()) {
        mManager->load();
    }

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &FollowUpReminderAgent::reload);
    //Reload all each 24hours
    mTimer->start(24 * 60 * 60 * 1000);
}

FollowUpReminderAgent::~FollowUpReminderAgent()
{
}

void FollowUpReminderAgent::setEnableAgent(bool enabled)
{
    if (FollowUpReminderAgentSettings::self()->enabled() == enabled) {
        return;
    }

    FollowUpReminderAgentSettings::self()->setEnabled(enabled);
    FollowUpReminderAgentSettings::self()->save();
    if (enabled) {
        mManager->load();
        mTimer->start();
    } else {
        mTimer->stop();
    }
}

bool FollowUpReminderAgent::enabledAgent() const
{
    return FollowUpReminderAgentSettings::self()->enabled();
}

void FollowUpReminderAgent::itemAdded(const Akonadi::Item &item, const Akonadi::Collection &collection)
{
    if (!enabledAgent()) {
        return;
    }

    if (item.mimeType() != KMime::Message::mimeType()) {
        qCDebug(FOLLOWUPREMINDERAGENT_LOG) << "FollowUpReminderAgent::itemAdded called for a non-message item!";
        return;
    }
    mManager->checkFollowUp(item, collection);
}

void FollowUpReminderAgent::reload()
{
    if (enabledAgent()) {
        mManager->load(true);
        mTimer->start();
    }
}

void FollowUpReminderAgent::addReminder(const QString &messageId, Akonadi::Item::Id messageItemId, const QString &to, const QString &subject, const QDate &followupDate, Akonadi::Item::Id todoId)
{
    auto info = new FollowUpReminder::FollowUpReminderInfo();
    info->setMessageId(messageId);
    info->setOriginalMessageItemId(messageItemId);
    info->setTo(to);
    info->setSubject(subject);
    info->setFollowUpReminderDate(followupDate);
    info->setTodoId(todoId);

    mManager->addReminder(info);
}

QString FollowUpReminderAgent::printDebugInfo() const
{
    return mManager->printDebugInfo();
}

AKONADI_AGENT_MAIN(FollowUpReminderAgent)
