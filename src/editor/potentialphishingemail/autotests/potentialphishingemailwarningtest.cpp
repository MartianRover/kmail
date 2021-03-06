/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "potentialphishingemailwarningtest.h"
#include "../potentialphishingemailwarning.h"
#include <QAction>
#include <QTest>

PotentialPhishingEmailWarningTest::PotentialPhishingEmailWarningTest(QObject *parent)
    : QObject(parent)
{
}

PotentialPhishingEmailWarningTest::~PotentialPhishingEmailWarningTest()
{
}

void PotentialPhishingEmailWarningTest::shouldHaveDefaultValue()
{
    PotentialPhishingEmailWarning w;
    QVERIFY(!w.isVisible());
    //Verify QVERIFY(w.isCloseButtonVisible());
    QAction *act = w.findChild<QAction *>(QStringLiteral("sendnow"));
    QVERIFY(act);
}

QTEST_MAIN(PotentialPhishingEmailWarningTest)
