/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef FOLDERARCHIVECACHE_H
#define FOLDERARCHIVECACHE_H

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <AkonadiCore/Collection>

class FolderArchiveAccountInfo;

struct ArchiveCache {
    QDate date = QDate::currentDate();
    Akonadi::Collection::Id colId = -1;
};

class FolderArchiveCache : public QObject
{
    Q_OBJECT
public:
    explicit FolderArchiveCache(QObject *parent = nullptr);
    ~FolderArchiveCache();

    void addToCache(const QString &resourceName, Akonadi::Collection::Id id);

    Q_REQUIRED_RESULT Akonadi::Collection::Id collectionId(FolderArchiveAccountInfo *info);

    void clearCacheWithContainsCollection(Akonadi::Collection::Id id);

    void clearCache();

private:
    Q_DISABLE_COPY(FolderArchiveCache)
    QHash<QString, ArchiveCache> mCache;
};

#endif // FOLDERARCHIVECACHE_H
