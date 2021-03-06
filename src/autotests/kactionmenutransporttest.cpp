/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "kactionmenutransporttest.h"
#include "../widgets/kactionmenutransport.h"
#include <QTest>
#include <QMenu>
KActionMenuTransportTest::KActionMenuTransportTest(QObject *parent)
    : QObject(parent)
{
}

KActionMenuTransportTest::~KActionMenuTransportTest()
{
}

void KActionMenuTransportTest::shouldHaveDefaultValue()
{
    KActionMenuTransport w;
    QVERIFY(w.menu());
    QCOMPARE(w.menu()->actions().count(), 0);
}

QTEST_MAIN(KActionMenuTransportTest)
