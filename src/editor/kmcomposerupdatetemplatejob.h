/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KMCOMPOSERUPDATETEMPLATEJOB_H
#define KMCOMPOSERUPDATETEMPLATEJOB_H

#include <QObject>
#include <KMime/Message>
#include <AkonadiCore/Collection>
#include <KIdentityManagement/Identity>

class KMComposerUpdateTemplateJob : public QObject
{
    Q_OBJECT
public:
    explicit KMComposerUpdateTemplateJob(QObject *parent = nullptr);
    ~KMComposerUpdateTemplateJob();
    void start();
    void setMsg(const KMime::Message::Ptr &msg);

    void setCustomTemplate(const QString &customTemplate);

    void setTextSelection(const QString &textSelection);

    void setWasModified(bool wasModified);

    void setUoldId(uint uoldId);

    void setUoid(uint uoid);

    void setIdent(const KIdentityManagement::Identity &ident);

    void setCollection(const Akonadi::Collection &col);
Q_SIGNALS:
    void updateComposer(const KIdentityManagement::Identity &ident, const KMime::Message::Ptr &msg, uint uoid, uint uoldId, bool wasModified);

private:
    Q_DISABLE_COPY(KMComposerUpdateTemplateJob)
    void slotFinished();

    QString mTextSelection;
    QString mCustomTemplate;
    KMime::Message::Ptr mMsg;
    Akonadi::Collection mCollectionForNewMessage;
    uint mUoldId = 0;
    uint mUoid = 0;
    KIdentityManagement::Identity mIdent;
    bool mWasModified = false;
};

#endif // KMCOMPOSERUPDATETEMPLATEJOB_H
