/*
   SPDX-FileCopyrightText: 2011-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TAGSELECTDIALOG_H
#define TAGSELECTDIALOG_H

#include "kmail_private_export.h"
#include <QDialog>
#include <QVector>
#include <AkonadiCore/Item>
#include <AkonadiCore/Tag>
#include "MailCommon/Tag"

class QListWidget;
class KActionCollection;
class KMAILTESTS_TESTS_EXPORT TagSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TagSelectDialog(QWidget *parent, int numberOfSelectedMessages, const Akonadi::Item &selectedItem);
    ~TagSelectDialog();
    Q_REQUIRED_RESULT Akonadi::Tag::List selectedTag() const;

    void setActionCollection(const QList<KActionCollection *> &actionCollectionList);

private:
    void slotAddNewTag();
    void slotTagsFetched(KJob *);
    void writeConfig();
    void readConfig();
    void createTagList(bool updateList);
    enum ItemType {
        UrlTag = Qt::UserRole + 1
    };
    int mNumberOfSelectedMessages = -1;
    Akonadi::Item mSelectedItem;

    Akonadi::Tag::List mCurrentSelectedTags;
    QVector<MailCommon::Tag::Ptr> mTagList;
    QList<KActionCollection *> mActionCollectionList;
    QListWidget *mListTag = nullptr;
};

#endif /* TAGSELECTDIALOG_H */
