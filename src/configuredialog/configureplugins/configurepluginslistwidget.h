/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef KMAILCONFIGUREPLUGINSLISTWIDGET_H
#define KMAILCONFIGUREPLUGINSLISTWIDGET_H

#include <QVector>
#include <PimCommon/ConfigurePluginsListWidget>
#include <PimCommon/PluginUtil>
class ConfigurePluginsListWidget : public PimCommon::ConfigurePluginsListWidget
{
    Q_OBJECT
public:
    explicit ConfigurePluginsListWidget(QWidget *parent = nullptr);
    ~ConfigurePluginsListWidget() override;

    void save() override;
    void doLoadFromGlobalSettings() override;
    void doResetToDefaultsOther() override;
    void initialize() override;
    void defaults() override;

private:
    void slotConfigureClicked(const QString &configureGroupName, const QString &identifier);
    void initializeAgentPlugins();
    PimCommon::PluginUtilData createAgentPluginData(const QString &agentIdentifier, const QString &path);
    Q_REQUIRED_RESULT bool agentActivateState(const QString &agentIdentifier, const QString &pathName);
    void changeAgentActiveState(const QString &agentIdentifier, const QString &path, bool enable);
    void saveAkonadiAgent();
    QVector<PluginItem *> mPluginEditorItems;
    QVector<PluginItem *> mPluginMessageViewerItems;
    QVector<PluginItem *> mPluginCheckBeforeSendItems;
    QVector<PluginItem *> mPluginEditorInitItems;
    QVector<PluginItem *> mPluginEditorGrammarItems;
    QVector<PluginItem *> mPluginGenericItems;
    QVector<PluginItem *> mPluginWebEngineItems;
    QVector<PluginItem *> mPluginHeaderStyleItems;
    QVector<PluginItem *> mAgentPluginsItems;
    QVector<PluginItem *> mPluginConvertTextItems;
    QVector<PluginItem *> mPluginConfigureItems;
    QVector<PimCommon::PluginUtilData> mPluginUtilDataList;
};

#endif // KMAILCONFIGUREPLUGINSLISTWIDGET_H
