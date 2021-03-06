/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef IDENTITYEDITVCARDDIALOG_H
#define IDENTITYEDITVCARDDIALOG_H

#include <QDialog>

namespace Akonadi {
class AkonadiContactEditor;
}

class IdentityEditVcardDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IdentityEditVcardDialog(const QString &fileName, QWidget *parent = nullptr);
    ~IdentityEditVcardDialog();
    /**
    * @brief loadVcard load vcard in a contact editor
    * @param vcardFileName
    */
    void loadVcard(const QString &vcardFileName);
    /**
    * @brief saveVcard
    * @return The file path for current vcard.
    */
    Q_REQUIRED_RESULT QString saveVcard() const;

    void reject() override;
Q_SIGNALS:
    void vcardRemoved();

private:
    void slotDeleteCurrentVCard();
    void deleteCurrentVcard(bool deleteOnDisk);
    QString mVcardFileName;
    Akonadi::AkonadiContactEditor *mContactEditor = nullptr;
};

#endif // IDENTITYEDITVCARDDIALOG_H
