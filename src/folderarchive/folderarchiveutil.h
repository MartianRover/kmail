/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef FOLDERARCHIVEUTIL_H
#define FOLDERARCHIVEUTIL_H

#include <QString>
namespace FolderArchive {
namespace FolderArchiveUtil {
Q_REQUIRED_RESULT QString groupConfigPattern();
Q_REQUIRED_RESULT bool resourceSupportArchiving(const QString &resource);
Q_REQUIRED_RESULT QString configFileName();
}
}

#endif // FOLDERARCHIVEUTIL_H
