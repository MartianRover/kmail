/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef ADDEMAILTOEXISTINGCONTACTDIALOG_H
#define ADDEMAILTOEXISTINGCONTACTDIALOG_H

#include <QDialog>
class QPushButton;
namespace Akonadi {
class EmailAddressSelectionWidget;
class Item;
}
class AddEmailToExistingContactDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddEmailToExistingContactDialog(QWidget *parent);
    ~AddEmailToExistingContactDialog();

    Q_REQUIRED_RESULT Akonadi::Item selectedContact() const;

private:
    void slotSelectionChanged();

    void slotDoubleClicked();
    void readConfig();
    void writeConfig();
    Akonadi::EmailAddressSelectionWidget *mEmailSelectionWidget = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif // ADDEMAILTOEXISTINGCONTACTDIALOG_H
