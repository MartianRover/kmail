/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PLUGININFOSOURCE_H
#define PLUGININFOSOURCE_H
#include <KUserFeedback/AbstractDataSource>
#include "kmail_private_export.h"

class KMAILTESTS_TESTS_EXPORT PluginInfoSource : public KUserFeedback::AbstractDataSource
{
public:
    PluginInfoSource();

    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT QString description() const override;

    Q_REQUIRED_RESULT QVariant data() override;
};

#endif // PLUGININFOSOURCE_H
