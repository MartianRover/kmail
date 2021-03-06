/*
   SPDX-FileCopyrightText: 2018 Daniel Vrátil <dvratil@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILKERNEL_H
#define MAILKERNEL_H

#include <QObject>
#include <MailCommon/MailInterfaces>

namespace Akonadi {
class EntityTreeModel;
class EntityMimeTypeFilterModel;
}

namespace MailCommon {
class FolderCollectionMonitor;
}

class MailKernel : public QObject, public MailCommon::IKernel, public MailCommon::ISettings
{
    Q_OBJECT
public:
    explicit MailKernel(const KSharedConfigPtr &config, QObject *parent = nullptr);
    ~MailKernel() override;

    KIdentityManagement::IdentityManager *identityManager() override;
    MessageComposer::MessageSender *msgSender() override;

    Akonadi::EntityMimeTypeFilterModel *collectionModel() const override;
    KSharedConfig::Ptr config() override;
    void syncConfig() override;
    MailCommon::JobScheduler *jobScheduler() const override;
    Akonadi::ChangeRecorder *folderCollectionMonitor() const override;
    void updateSystemTray() override;

    qreal closeToQuotaThreshold() override;
    bool excludeImportantMailFromExpiry() override;
    QStringList customTemplates() override;
    Akonadi::Collection::Id lastSelectedFolder() override;
    void setLastSelectedFolder(Akonadi::Collection::Id col) override;
    bool showPopupAfterDnD() override;
    void expunge(Akonadi::Collection::Id id, bool sync) override;

private:
    Q_DISABLE_COPY(MailKernel)

    KSharedConfigPtr mConfig;
    KIdentityManagement::IdentityManager *mIdentityManager = nullptr;
    MessageComposer::MessageSender *mMessageSender = nullptr;
    MailCommon::FolderCollectionMonitor *mFolderCollectionMonitor = nullptr;
    Akonadi::EntityTreeModel *mEntityTreeModel = nullptr;
    Akonadi::EntityMimeTypeFilterModel *mCollectionModel = nullptr;
};

#endif
