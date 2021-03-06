/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kmcomposercreatenewcomposerjob.h"
#include "kmkernel.h"
#include "composer.h"
#include "editor/kmcomposerwin.h"

#include <KMime/Message>
#include <MessageComposer/MessageHelper>
#include <TemplateParser/TemplateParserJob>

KMComposerCreateNewComposerJob::KMComposerCreateNewComposerJob(QObject *parent)
    : QObject(parent)
{
}

KMComposerCreateNewComposerJob::~KMComposerCreateNewComposerJob()
{
}

void KMComposerCreateNewComposerJob::start()
{
    mMsg = KMime::Message::Ptr(new KMime::Message());

    MessageHelper::initHeader(mMsg, KMKernel::self()->identityManager(), mCurrentIdentity);
    TemplateParser::TemplateParserJob *parser = new TemplateParser::TemplateParserJob(mMsg, TemplateParser::TemplateParserJob::NewMessage, this);
    connect(parser, &TemplateParser::TemplateParserJob::parsingDone, this, &KMComposerCreateNewComposerJob::slotCreateNewComposer);
    parser->setIdentityManager(KMKernel::self()->identityManager());
    parser->process(mMsg, mCollectionForNewMessage.id());
}

void KMComposerCreateNewComposerJob::slotCreateNewComposer(bool forceCursorPosition)
{
    KMail::Composer *win = KMComposerWin::create(mMsg, false, false, KMail::Composer::New, mCurrentIdentity);
    win->setCollectionForNewMessage(mCollectionForNewMessage);
    if (forceCursorPosition) {
        win->setFocusToEditor();
    }
    win->show();
    deleteLater();
}

void KMComposerCreateNewComposerJob::setCurrentIdentity(uint currentIdentity)
{
    mCurrentIdentity = currentIdentity;
}

void KMComposerCreateNewComposerJob::setCollectionForNewMessage(const Akonadi::Collection &collectionForNewMessage)
{
    mCollectionForNewMessage = collectionForNewMessage;
}
