/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "archivemailwidgettest.h"
#include "../archivemailwidget.h"

#include <QTest>
#include <QTreeWidget>
#include <QStandardPaths>

ArchiveMailWidgetTest::ArchiveMailWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ArchiveMailWidgetTest::~ArchiveMailWidgetTest()
{
}

void ArchiveMailWidgetTest::shouldHaveDefaultValue()
{
    QWidget parent;
    new QHBoxLayout(&parent);
    ArchiveMailWidget mailwidget({}, &parent, {QStringLiteral("akonadi_archivemail_agent")});

    QTreeWidget *treeWidget = parent.findChild<QTreeWidget *>(QStringLiteral("treewidget"));
    QVERIFY(treeWidget);

    QCOMPARE(treeWidget->topLevelItemCount(), 0);
}

QTEST_MAIN(ArchiveMailWidgetTest)
