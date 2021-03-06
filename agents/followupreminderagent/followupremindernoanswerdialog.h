/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLLOWUPREMINDERNOANSWERDIALOG_H
#define FOLLOWUPREMINDERNOANSWERDIALOG_H

#include <QDialog>
namespace FollowUpReminder {
class FollowUpReminderInfo;
}
class FollowUpReminderInfoWidget;
class FollowUpReminderNoAnswerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FollowUpReminderNoAnswerDialog(QWidget *parent = nullptr);
    ~FollowUpReminderNoAnswerDialog();

    void setInfo(const QList<FollowUpReminder::FollowUpReminderInfo *> &info);

    void wakeUp();
Q_SIGNALS:
    void needToReparseConfiguration();

private:
    void slotDBusNotificationsPropertiesChanged(const QString &interface, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);
    void slotSave();
    void readConfig();
    void writeConfig();
    FollowUpReminderInfoWidget *mWidget = nullptr;
};

#endif // FOLLOWUPREMINDERNOANSWERDIALOG_H
