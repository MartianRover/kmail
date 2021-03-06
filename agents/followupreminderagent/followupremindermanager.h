/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLLOWUPREMINDERMANAGER_H
#define FOLLOWUPREMINDERMANAGER_H

#include <QObject>
#include <KSharedConfig>
#include <AkonadiCore/Item>
#include <QPointer>
namespace FollowUpReminder {
class FollowUpReminderInfo;
}
class FollowUpReminderNoAnswerDialog;
class FollowUpReminderManager : public QObject
{
    Q_OBJECT
public:
    explicit FollowUpReminderManager(QObject *parent = nullptr);
    ~FollowUpReminderManager();

    void load(bool forceReloadConfig = false);
    void addReminder(FollowUpReminder::FollowUpReminderInfo *reminder); // takes ownership
    void checkFollowUp(const Akonadi::Item &item, const Akonadi::Collection &col);

    Q_REQUIRED_RESULT QString printDebugInfo() const;
private:
    Q_DISABLE_COPY(FollowUpReminderManager)
    void slotCheckFollowUpFinished(const QString &messageId, Akonadi::Item::Id id);

    void slotFinishTaskDone();
    void slotFinishTaskFailed();
    void slotReparseConfiguration();
    void answerReceived(const QString &from);
    Q_REQUIRED_RESULT QString infoToStr(FollowUpReminder::FollowUpReminderInfo *info) const;

    KSharedConfig::Ptr mConfig;
    QList<FollowUpReminder::FollowUpReminderInfo *> mFollowUpReminderInfoList;
    QPointer<FollowUpReminderNoAnswerDialog> mNoAnswerDialog;
    bool mInitialize = false;
};

#endif // FOLLOWUPREMINDERMANAGER_H
