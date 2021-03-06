/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLLOWUPREMINDERFINISHTASKJOB_H
#define FOLLOWUPREMINDERFINISHTASKJOB_H

#include <QObject>
#include <AkonadiCore/Item>
class KJob;
class FollowUpReminderFinishTaskJob : public QObject
{
    Q_OBJECT
public:
    explicit FollowUpReminderFinishTaskJob(Akonadi::Item::Id id, QObject *parent = nullptr);
    ~FollowUpReminderFinishTaskJob();

    void start();

Q_SIGNALS:
    void finishTaskDone();
    void finishTaskFailed();

private:
    Q_DISABLE_COPY(FollowUpReminderFinishTaskJob)
    void slotItemFetchJobDone(KJob *job);
    void slotItemModifiedResult(KJob *job);
    void closeTodo();
    Akonadi::Item::Id mTodoId;
};

#endif // FOLLOWUPREMINDERFINISHTASKJOB_H
