/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLLOWUPREMINDERINFOCONFIGWIDGET_H
#define FOLLOWUPREMINDERINFOCONFIGWIDGET_H

#include <QWidget>
#include <QVariantList>
#include <AkonadiCore/Item>
#include <AkonadiCore/AgentConfigurationBase>
class FollowUpReminderInfoWidget;
namespace FollowUpReminder {
class FollowUpReminderInfo;
}

class FollowUpReminderInfoConfigWidget : public Akonadi::AgentConfigurationBase
{
    Q_OBJECT
public:
    explicit FollowUpReminderInfoConfigWidget(const KSharedConfigPtr &config, QWidget *parentWidget, const QVariantList &args);
    ~FollowUpReminderInfoConfigWidget() override;

    bool save() const override;
    void load() override;
    QSize restoreDialogSize() const override;
    void saveDialogSize(const QSize &size) override;
private:
    FollowUpReminderInfoWidget *mWidget = nullptr;
};
AKONADI_AGENTCONFIG_FACTORY(FollowUpReminderInfoAgentConfigFactory, "followupreminderagentconfig.json", FollowUpReminderInfoConfigWidget)
#endif // FOLLOWUPREMINDERINFOConfigWIDGET_H
