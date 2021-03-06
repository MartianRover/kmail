/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXTERNALEDITORWARNING_H
#define EXTERNALEDITORWARNING_H

#include <KMessageWidget>
#include "kmail_private_export.h"
class KMAILTESTS_TESTS_EXPORT ExternalEditorWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit ExternalEditorWarning(QWidget *parent = nullptr);
    ~ExternalEditorWarning();
};

#endif // EXTERNALEDITORWARNING_H
