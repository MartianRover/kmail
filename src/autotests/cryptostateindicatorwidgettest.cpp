/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "cryptostateindicatorwidgettest.h"
#include <QTest>
#include "src/editor/widgets/cryptostateindicatorwidget.h"
#include <QLabel>
CryptoStateIndicatorWidgetTest::CryptoStateIndicatorWidgetTest(QObject *parent) : QObject(parent)
{
}

CryptoStateIndicatorWidgetTest::~CryptoStateIndicatorWidgetTest()
{
}

void CryptoStateIndicatorWidgetTest::shouldHaveDefaultValue()
{
    CryptoStateIndicatorWidget w;
    w.show();
    QVERIFY(QTest::qWaitForWindowExposed(&w));
    QLabel *signature = w.findChild<QLabel *>(QStringLiteral("signatureindicator"));
    QVERIFY(signature);
    QLabel *encryption = w.findChild<QLabel *>(QStringLiteral("encryptionindicator"));
    QVERIFY(encryption);
    QVERIFY(signature->isVisible());
    QVERIFY(encryption->isVisible());
}

void CryptoStateIndicatorWidgetTest::shouldBeNotVisibleWhenShowAlwaysIsFalse()
{
    CryptoStateIndicatorWidget w;
    w.setShowAlwaysIndicator(false);
    w.show();
    QLabel *signature = w.findChild<QLabel *>(QStringLiteral("signatureindicator"));
    QLabel *encryption = w.findChild<QLabel *>(QStringLiteral("encryptionindicator"));
    QVERIFY(!signature->isVisible());
    QVERIFY(!encryption->isVisible());
    w.updateSignatureAndEncrypionStateIndicators(true, true);

    QVERIFY(!signature->isVisible());
    QVERIFY(!encryption->isVisible());
}

void CryptoStateIndicatorWidgetTest::shouldVisibleWhenChangeStatus()
{
    CryptoStateIndicatorWidget w;
    w.setShowAlwaysIndicator(true);
    w.show();
    QVERIFY(QTest::qWaitForWindowExposed(&w));
    QLabel *signature = w.findChild<QLabel *>(QStringLiteral("signatureindicator"));
    QLabel *encryption = w.findChild<QLabel *>(QStringLiteral("encryptionindicator"));
    w.updateSignatureAndEncrypionStateIndicators(true, false);
    QVERIFY(signature->isVisible());
    QVERIFY(!encryption->isVisible());

    w.updateSignatureAndEncrypionStateIndicators(false, true);
    QVERIFY(!signature->isVisible());
    QVERIFY(encryption->isVisible());

    w.updateSignatureAndEncrypionStateIndicators(true, true);
    QVERIFY(signature->isVisible());
    QVERIFY(encryption->isVisible());

    w.updateSignatureAndEncrypionStateIndicators(false, false);
    QVERIFY(!signature->isVisible());
    QVERIFY(!encryption->isVisible());
}

QTEST_MAIN(CryptoStateIndicatorWidgetTest)
