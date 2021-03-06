/*

    This file is part of KMail.
    SPDX-FileCopyrightText: 2002-2003 Don Sanders <sanders@kde.org>,
    SPDX-FileCopyrightText: 2003 Zack Rusin <zack@kde.org>,
    Based on the work of Cornelius Schumacher <schumacher@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later WITH Qt-Commercial-exception-1.0
*/

#include "kmail_part.h"

#include "kmmainwin.h"
#include "kmmainwidget.h"

#include <QVBoxLayout>

#include <KParts/GUIActivateEvent>
#include <kparts/statusbarextension.h>
#include <kparts/mainwindow.h>
#include <KPluginFactory>
#include "kmail_debug.h"
#include <ksettings/dispatcher.h>
#include <kmailpartadaptor.h>
#include <AkonadiCore/collection.h>
#include <AkonadiCore/entitydisplayattribute.h>
#include <AkonadiCore/changerecorder.h>
#include <MailCommon/FolderTreeView>
#include "tag/tagactionmanager.h"
#include "foldershortcutactionmanager.h"
#include "kmmigrateapplication.h"
#include <KLocalizedString>
#include <KSharedConfig>

K_PLUGIN_FACTORY(KMailFactory, registerPlugin<KMailPart>();
                 )

using namespace KMail;

KMailPart::KMailPart(QWidget *parentWidget, QObject *parent, const QVariantList &)
    : KParts::ReadOnlyPart(parent)
    , mParentWidget(parentWidget)
{
    setComponentName(QStringLiteral("kmail2"), i18n("KMail2"));

    KMMigrateApplication migrate;
    migrate.migrate();

    //local, do the init
    KMKernel *mKMailKernel = new KMKernel();
    mKMailKernel->init();
    mKMailKernel->setXmlGuiInstanceName(QStringLiteral("kmail2"));

    // and session management
    mKMailKernel->doSessionManagement();

    // any dead letters?
    mKMailKernel->recoverDeadLetters();

    kmkernel->setupDBus(); // Ok. We are ready for D-Bus requests.
    (void)new KmailpartAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/KMailPart"), this);

    // create a canvas to insert our widget
    QWidget *canvas = new QWidget(parentWidget);
    canvas->setFocusPolicy(Qt::ClickFocus);
    canvas->setObjectName(QStringLiteral("canvas"));
    setWidget(canvas);
    mainWidget = new KMMainWidget(canvas, this, actionCollection(),
                                  KSharedConfig::openConfig());
    mainWidget->setObjectName(QStringLiteral("partmainwidget"));
    QVBoxLayout *topLayout = new QVBoxLayout(canvas);
    topLayout->addWidget(mainWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    mainWidget->setFocusPolicy(Qt::ClickFocus);
    KParts::StatusBarExtension *statusBar = new KParts::StatusBarExtension(this);
    statusBar->addStatusBarItem(mainWidget->vacationScriptIndicator(), 2, false);
    statusBar->addStatusBarItem(mainWidget->zoomLabelIndicator(), 3, false);
    statusBar->addStatusBarItem(mainWidget->dkimWidgetInfo(), 4, false);

    setXMLFile(QStringLiteral("kmail_part.rc"), true);
    KSettings::Dispatcher::registerComponent(QStringLiteral("kmail2"), mKMailKernel, "slotConfigChanged");
    connect(mainWidget, &KMMainWidget::captionChangeRequest, this, &KMailPart::setWindowCaption);
}

KMailPart::~KMailPart()
{
    qCDebug(KMAIL_LOG) << "Closing last KMMainWin: stopping mail check";
    // Running KIO jobs prevent kapp from exiting, so we need to kill them
    // if they are only about checking mail (not important stuff like moving messages)
    mainWidget->destruct();
    kmkernel->cleanup();
    delete kmkernel;
}

void KMailPart::updateQuickSearchText()
{
    mainWidget->updateQuickSearchLineText();
}

bool KMailPart::openFile()
{
    return true;
}

//-----------------------------------------------------------------------------

void KMailPart::guiActivateEvent(KParts::GUIActivateEvent *e)
{
    KParts::ReadOnlyPart::guiActivateEvent(e);
    if (e->activated()) {
        mainWidget->initializeFilterActions(true);
        mainWidget->tagActionManager()->createActions();
        mainWidget->folderShortcutActionManager()->createActions();
        mainWidget->populateMessageListStatusFilterCombo();
        mainWidget->initializePluginActions();

        const QString title = mainWidget->fullCollectionPath();
        if (!title.isEmpty()) {
            Q_EMIT setWindowCaption(title);
        }
    }
}

void KMailPart::exit()
{
    delete this;
}

QWidget *KMailPart::parentWidget() const
{
    return mParentWidget;
}

void KMailPart::save()
{
    /*TODO*/
}

#include "kmail_part.moc"
