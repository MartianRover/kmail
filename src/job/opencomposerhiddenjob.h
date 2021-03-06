/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef OPENCOMPOSERHIDDENJOB_H
#define OPENCOMPOSERHIDDENJOB_H

#include <QObject>
#include <KMime/Message>

struct OpenComposerHiddenJobSettings
{
    OpenComposerHiddenJobSettings()
    {
    }

    OpenComposerHiddenJobSettings(const QString &to, const QString &cc, const QString &bcc, const QString &subject, const QString &body, bool hidden)
        : mTo(to)
        , mCc(cc)
        , mBcc(bcc)
        , mSubject(subject)
        , mBody(body)
        , mHidden(hidden)
    {
    }

    QString mTo;
    QString mCc;
    QString mBcc;
    QString mSubject;
    QString mBody;
    bool mHidden = false;
};

class OpenComposerHiddenJob : public QObject
{
    Q_OBJECT
public:
    explicit OpenComposerHiddenJob(QObject *parent = nullptr);
    ~OpenComposerHiddenJob();
    void start();
    void setSettings(const OpenComposerHiddenJobSettings &settings);

private:
    Q_DISABLE_COPY(OpenComposerHiddenJob)
    void slotOpenComposer();
    OpenComposerHiddenJobSettings mSettings;
    KMime::Message::Ptr mMsg = nullptr;
};

#endif // OPENCOMPOSERHIDDENJOB_H
