/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externaleditorwarningtest.h"
#include "../externaleditorwarning.h"
#include <QHBoxLayout>
#include <QTest>

QTEST_MAIN(ExternalEditorWarningTest)

ExternalEditorWarningTest::ExternalEditorWarningTest(QObject *parent)
    : QObject(parent)
{
}

void ExternalEditorWarningTest::shouldHaveDefaultValue()
{
    QWidget *wid = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(wid);
    ExternalEditorWarning w;
    layout->addWidget(&w);
    wid->show();
    QVERIFY(!w.isVisible());
    //QVERIFY(w.isCloseButtonVisible());
    QCOMPARE(w.messageType(), KMessageWidget::Information);
    QVERIFY(w.wordWrap());
    QVERIFY(!w.text().isEmpty());
}
