/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLLOWUPREMINDERCONFIGTEST_H
#define FOLLOWUPREMINDERCONFIGTEST_H

#include <QObject>
#include <QRegularExpression>
#include <KSharedConfig>

class FollowUpReminderConfigTest : public QObject
{
    Q_OBJECT
public:
    explicit FollowUpReminderConfigTest(QObject *parent = nullptr);
    ~FollowUpReminderConfigTest();
private Q_SLOTS:
    void init();
    void cleanup();
    void cleanupTestCase();
    void shouldConfigBeEmpty();
    void shouldAddAnItem();
    void shouldNotAddAnInvalidItem();
    void shouldReplaceItem();
    void shouldAddSeveralItem();
    void shouldRemoveItems();
    void shouldNotRemoveItemWhenListIsEmpty();
    void shouldNotRemoveItemWhenItemDoesntExist();

private:
    KSharedConfig::Ptr mConfig;
    QRegularExpression mFollowupRegExpFilter;
};

#endif // FOLLOWUPREMINDERCONFIGTEST_H
