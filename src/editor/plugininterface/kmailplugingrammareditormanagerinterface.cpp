/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kmailplugingrammareditormanagerinterface.h"
#include "kmail_debug.h"
#include <PimCommon/CustomToolsWidgetng>
#include <PimCommon/CustomToolsPlugin>
#include <MessageComposer/PluginEditorGrammarManager>
#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>

KMailPluginGrammarEditorManagerInterface::KMailPluginGrammarEditorManagerInterface(QObject *parent)
    : QObject(parent)
{
}

KPIMTextEdit::RichTextComposer *KMailPluginGrammarEditorManagerInterface::richTextEditor() const
{
    return mRichTextEditor;
}

void KMailPluginGrammarEditorManagerInterface::setRichTextEditor(KPIMTextEdit::RichTextComposer *richTextEditor)
{
    mRichTextEditor = richTextEditor;
}

QWidget *KMailPluginGrammarEditorManagerInterface::parentWidget() const
{
    return mParentWidget;
}

void KMailPluginGrammarEditorManagerInterface::setParentWidget(QWidget *parentWidget)
{
    mParentWidget = parentWidget;
}

KActionCollection *KMailPluginGrammarEditorManagerInterface::actionCollection() const
{
    return mActionCollection;
}

void KMailPluginGrammarEditorManagerInterface::setActionCollection(KActionCollection *actionCollection)
{
    mActionCollection = actionCollection;
}

PimCommon::CustomToolsWidgetNg *KMailPluginGrammarEditorManagerInterface::customToolsWidget() const
{
    return mCustomToolsWidget;
}

void KMailPluginGrammarEditorManagerInterface::setCustomToolsWidget(PimCommon::CustomToolsWidgetNg *customToolsWidget)
{
    mCustomToolsWidget = customToolsWidget;
}

void KMailPluginGrammarEditorManagerInterface::initializePlugins()
{
    if (mWasInitialized) {
        qCDebug(KMAIL_LOG) << "KMailPluginGrammarEditorManagerInterface : Plugin was already initialized. This is a bug";
        return;
    }
    if (!mRichTextEditor) {
        qCDebug(KMAIL_LOG) << "KMailPluginGrammarEditorManagerInterface : Richtexteditor is null. This is a bug";
        return;
    }
    if (!mParentWidget) {
        qCDebug(KMAIL_LOG) << "KMailPluginGrammarEditorManagerInterface : Parent is null. This is a bug";
    }
    if (!mCustomToolsWidget) {
        qCDebug(KMAIL_LOG) << "KMailPluginGrammarEditorManagerInterface : mCustomToolsWidget is null. This is a bug";
        return;
    }

    const QVector<PimCommon::CustomToolsPlugin *> lstPlugin = MessageComposer::PluginEditorGrammarManager::self()->pluginsList();
    for (PimCommon::CustomToolsPlugin *plugin : lstPlugin) {
        if (plugin->isEnabled()) {
            MessageComposer::PluginEditorGrammarCustomToolsViewInterface *interface = static_cast<MessageComposer::PluginEditorGrammarCustomToolsViewInterface *>(plugin->createView(mActionCollection, mCustomToolsWidget));
            mCustomToolsWidget->addCustomToolViewInterface(interface);
            interface->setParentWidget(mParentWidget);
            interface->setRichTextEditor(mRichTextEditor);
        }
    }
    mWasInitialized = true;
}
