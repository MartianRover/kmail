/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef UNITCOMBOBOXTEST_H
#define UNITCOMBOBOXTEST_H

#include <QObject>

class UnitComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit UnitComboBoxTest(QObject *parent = nullptr);
    ~UnitComboBoxTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void changeCurrentItem();
    void changeCurrentItem_data();
};

#endif // UNITCOMBOBOXTEST_H
