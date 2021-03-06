/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef IDENTITYADDVCARDDIALOG_H
#define IDENTITYADDVCARDDIALOG_H
#include "kmail_private_export.h"
#include <QDialog>
#include <QUrl>
class QButtonGroup;
class QComboBox;
class KUrlRequester;

class KMAILTESTS_TESTS_EXPORT IdentityAddVcardDialog : public QDialog
{
    Q_OBJECT
public:
    enum DuplicateMode {
        Empty,
        ExistingEntry,
        FromExistingVCard
    };

    explicit IdentityAddVcardDialog(const QStringList &shadowIdentities, QWidget *parent = nullptr);
    ~IdentityAddVcardDialog();

    Q_REQUIRED_RESULT DuplicateMode duplicateMode() const;
    Q_REQUIRED_RESULT QString duplicateVcardFromIdentity() const;
    Q_REQUIRED_RESULT QUrl existingVCard() const;

private:
    QButtonGroup *mButtonGroup = nullptr;
    QComboBox *mComboBox = nullptr;
    KUrlRequester *mVCardPath = nullptr;
};

#endif // IDENTITYADDVCARDDIALOG_H
