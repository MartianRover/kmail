/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "followupremindernoanswerdialog.h"
#include "followupreminderinfowidget.h"
#include "followupreminderinfo.h"
#include "followupreminderagent_debug.h"

#include <KLocalizedString>
#include <KSharedConfig>

#include <QLabel>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QPushButton>
#include <QVBoxLayout>

#include "notifications_interface.h" // DBUS-generated
#include "dbusproperties.h" // DBUS-generated

namespace {
static constexpr const char s_fdo_notifications_service[] = "org.freedesktop.Notifications";
static constexpr const char s_fdo_notifications_path[] = "/org/freedesktop/Notifications";
static constexpr const char DialogGroup[] = "FollowUpReminderNoAnswerDialog";
}

FollowUpReminderNoAnswerDialog::FollowUpReminderNoAnswerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Follow Up Reminder"));
    setWindowIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *lab = new QLabel(i18n("You still wait an answer about this mail:"), this);
    mainLayout->addWidget(lab);
    mWidget = new FollowUpReminderInfoWidget(this);
    mWidget->setObjectName(QStringLiteral("FollowUpReminderInfoWidget"));
    mainLayout->addWidget(mWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FollowUpReminderNoAnswerDialog::slotSave);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &FollowUpReminderNoAnswerDialog::reject);

    mainLayout->addWidget(buttonBox);

    readConfig();
    QDBusConnection dbusConn = QDBusConnection::sessionBus();
    if (dbusConn.interface()->isServiceRegistered(QString::fromLatin1(s_fdo_notifications_service))) {
        OrgFreedesktopDBusPropertiesInterface *propsIface = new OrgFreedesktopDBusPropertiesInterface(
            QString::fromLatin1(s_fdo_notifications_service),
            QString::fromLatin1(s_fdo_notifications_path),
            dbusConn, this);
        connect(propsIface, &OrgFreedesktopDBusPropertiesInterface::PropertiesChanged,
                this, &FollowUpReminderNoAnswerDialog::slotDBusNotificationsPropertiesChanged);
    }
}

FollowUpReminderNoAnswerDialog::~FollowUpReminderNoAnswerDialog()
{
    writeConfig();
}

void FollowUpReminderNoAnswerDialog::wakeUp()
{
    // Check if notifications are inhibited (e.x. plasma "do not disturb" mode.
    // In that case, we'll wait until they are allowed again (see slotDBusNotificationsPropertiesChanged)
    QDBusConnection dbusConn = QDBusConnection::sessionBus();
    if (dbusConn.interface()->isServiceRegistered(QString::fromLatin1(s_fdo_notifications_service))) {
        OrgFreedesktopNotificationsInterface iface(
            QString::fromLatin1(s_fdo_notifications_service),
            QString::fromLatin1(s_fdo_notifications_path),
            dbusConn);
        if (iface.inhibited()) {
            return;
        }
    }
    show();
}

void FollowUpReminderNoAnswerDialog::slotDBusNotificationsPropertiesChanged(
    const QString &interface, const QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(interface); // always "org.freedesktop.Notifications"
    Q_UNUSED(invalidatedProperties);
    const auto it = changedProperties.find(QStringLiteral("Inhibited"));
    if (it != changedProperties.end()) {
        const bool inhibited = it.value().toBool();
        qCDebug(FOLLOWUPREMINDERAGENT_LOG) << "Notifications inhibited:" << inhibited;
        if (!inhibited) {
            wakeUp();
        }
    }
}

void FollowUpReminderNoAnswerDialog::setInfo(const QList<FollowUpReminder::FollowUpReminderInfo *> &info)
{
    mWidget->setInfo(info);
}

void FollowUpReminderNoAnswerDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), DialogGroup);
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
    mWidget->restoreTreeWidgetHeader(group.readEntry("HeaderState", QByteArray()));
}

void FollowUpReminderNoAnswerDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), DialogGroup);
    group.writeEntry("Size", size());
    mWidget->saveTreeWidgetHeader(group);
}

void FollowUpReminderNoAnswerDialog::slotSave()
{
    if (mWidget->save()) {
        Q_EMIT needToReparseConfiguration();
    }
    accept();
}
