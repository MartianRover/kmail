/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "potentialphishingdetaildialogtest.h"
#include "../potentialphishingdetaildialog.h"
#include "../potentialphishingdetailwidget.h"
#include <QTest>
#include <QStandardPaths>
PotentialPhishingDetailDialogTest::PotentialPhishingDetailDialogTest(QObject *parent)
    : QObject(parent)
{
}

PotentialPhishingDetailDialogTest::~PotentialPhishingDetailDialogTest()
{
}

void PotentialPhishingDetailDialogTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void PotentialPhishingDetailDialogTest::shouldHaveDefaultValue()
{
    PotentialPhishingDetailDialog dlg;
    PotentialPhishingDetailWidget *w = dlg.findChild<PotentialPhishingDetailWidget *>(QStringLiteral("potentialphising_widget"));
    QVERIFY(w);
}

QTEST_MAIN(PotentialPhishingDetailDialogTest)
