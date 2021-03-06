/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef IDENTITYFOLDERREQUESTER_H
#define IDENTITYFOLDERREQUESTER_H

#include <MailCommon/FolderRequester>

namespace Akonadi {
class Collection;
}

namespace KMail {
class IdentityFolderRequester : public MailCommon::FolderRequester
{
    Q_OBJECT
public:
    explicit IdentityFolderRequester(QWidget *parent = nullptr);
    ~IdentityFolderRequester();

    void setIsInvalidFolder(const Akonadi::Collection &col);
private:
    void slotFolderChanged(const Akonadi::Collection &col);
};
}
#endif // IDENTITYFOLDERREQUESTER_H
