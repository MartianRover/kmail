/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INCORRECTIDENTITYFOLDERWARNING_H
#define INCORRECTIDENTITYFOLDERWARNING_H

#include <KMessageWidget>
#include "kmail_private_export.h"

class KMAILTESTS_TESTS_EXPORT IncorrectIdentityFolderWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit IncorrectIdentityFolderWarning(QWidget *parent = nullptr);
    ~IncorrectIdentityFolderWarning();

    void mailTransportIsInvalid();
    void fccIsInvalid();
    void identityInvalid();
    void dictionaryInvalid();
    void clearFccInvalid();

private:
    void addNewLine(QString &str);
    void updateText();
    void slotHideAnnimationFinished();
    bool mMailTransportIsInvalid = false;
    bool mFccIsInvalid = false;
    bool mIdentityIsInvalid = false;
    bool mDictionaryIsInvalid = false;
};

#endif // INCORRECTIDENTITYFOLDERWARNING_H
