/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kmailplugineditormanagerinterface.h"
#include <MessageComposer/PluginEditorManager>
#include <MessageComposer/PluginEditor>
#include <MessageComposer/PluginComposerInterface>
#include "kmail_debug.h"

#include <QAction>
#include <QVector>

KMailPluginEditorManagerInterface::KMailPluginEditorManagerInterface(QObject *parent)
    : QObject(parent)
{
}

KMailPluginEditorManagerInterface::~KMailPluginEditorManagerInterface()
{
}

KPIMTextEdit::RichTextEditor *KMailPluginEditorManagerInterface::richTextEditor() const
{
    return mRichTextEditor;
}

void KMailPluginEditorManagerInterface::setRichTextEditor(KPIMTextEdit::RichTextEditor *richTextEditor)
{
    mRichTextEditor = richTextEditor;
}

QWidget *KMailPluginEditorManagerInterface::parentWidget() const
{
    return mParentWidget;
}

void KMailPluginEditorManagerInterface::setParentWidget(QWidget *parentWidget)
{
    mParentWidget = parentWidget;
}

void KMailPluginEditorManagerInterface::initializePlugins()
{
    if (!mListPluginInterface.isEmpty()) {
        qCWarning(KMAIL_LOG) << "Plugin was already initialized. This is a bug";
        return;
    }
    if (!mRichTextEditor) {
        qCWarning(KMAIL_LOG) << "KMailPluginEditorManagerInterface: Missing richtexteditor";
        return;
    }
    if (!mParentWidget) {
        qCWarning(KMAIL_LOG) << "KMailPluginEditorManagerInterface : Parent is null. This is a bug";
    }

    const QVector<MessageComposer::PluginEditor *> lstPlugin = MessageComposer::PluginEditorManager::self()->pluginsList();
    for (MessageComposer::PluginEditor *plugin : lstPlugin) {
        if (plugin->isEnabled()) {
            MessageComposer::PluginEditorInterface *interface = static_cast<MessageComposer::PluginEditorInterface *>(plugin->createInterface(this));
            MessageComposer::PluginComposerInterface *composerInterface = new MessageComposer::PluginComposerInterface;
            composerInterface->setComposerViewBase(mComposerInterface);
            interface->setComposerInterface(composerInterface);
            interface->setRichTextEditor(mRichTextEditor);
            interface->setParentWidget(mParentWidget);
            interface->createAction(mActionCollection);
            interface->setPlugin(plugin);
            connect(interface, &MessageComposer::PluginEditorInterface::emitPluginActivated, this, &KMailPluginEditorManagerInterface::slotPluginActivated);
            connect(interface, &MessageComposer::PluginEditorInterface::message, this, &KMailPluginEditorManagerInterface::message);
            connect(interface, &MessageComposer::PluginEditorInterface::insertText, this, &KMailPluginEditorManagerInterface::insertText);
            mListPluginInterface.append(interface);
        }
    }
}

void KMailPluginEditorManagerInterface::slotPluginActivated(MessageComposer::PluginEditorInterface *interface)
{
    interface->exec();
}

MessageComposer::ComposerViewBase *KMailPluginEditorManagerInterface::composerInterface() const
{
    return mComposerInterface;
}

void KMailPluginEditorManagerInterface::setComposerInterface(MessageComposer::ComposerViewBase *composerInterface)
{
    mComposerInterface = composerInterface;
}

bool KMailPluginEditorManagerInterface::processProcessKeyEvent(QKeyEvent *event)
{
    if (!mListPluginInterface.isEmpty()) {
        for (MessageComposer::PluginEditorInterface *interface : qAsConst(mListPluginInterface)) {
            if (static_cast<MessageComposer::PluginEditor *>(interface->plugin())->canProcessKeyEvent()) {
                if (interface->processProcessKeyEvent(event)) {
                    return true;
                }
            }
        }
    }
    return false;
}

KActionCollection *KMailPluginEditorManagerInterface::actionCollection() const
{
    return mActionCollection;
}

void KMailPluginEditorManagerInterface::setActionCollection(KActionCollection *actionCollection)
{
    mActionCollection = actionCollection;
}

QList<QAction *> KMailPluginEditorManagerInterface::actionsType(MessageComposer::PluginActionType::Type type)
{
    return mActionHash.value(type);
}

QList<QWidget *> KMailPluginEditorManagerInterface::statusBarWidgetList()
{
    if (mStatusBarWidget.isEmpty() && !mListPluginInterface.isEmpty()) {
        for (MessageComposer::PluginEditorInterface *interface : qAsConst(mListPluginInterface)) {
            if (interface->plugin()->hasStatusBarSupport()) {
                mStatusBarWidget.append(interface->statusBarWidget());
            }
        }
    }
    return mStatusBarWidget;
}

QHash<MessageComposer::PluginActionType::Type, QList<QAction *> > KMailPluginEditorManagerInterface::actionsType()
{
    if (mActionHash.isEmpty() && !mListPluginInterface.isEmpty()) {
        for (MessageComposer::PluginEditorInterface *interface : qAsConst(mListPluginInterface)) {
            const MessageComposer::PluginActionType actionType = interface->actionType();
            MessageComposer::PluginActionType::Type type = actionType.type();
            const bool needSelectedText = interface->needSelectedText();
            if (needSelectedText) {
                //Disable by default as we don't have selection by default.
                actionType.action()->setEnabled(false);
                connect(this, &KMailPluginEditorManagerInterface::textSelectionChanged, actionType.action(), &QAction::setEnabled);
            }
            QList<QAction *> lst = mActionHash.value(type);
            if (!lst.isEmpty()) {
                QAction *act = new QAction(this);
                act->setSeparator(true);
                lst << act << actionType.action();
                mActionHash.insert(type, lst);
            } else {
                mActionHash.insert(type, QList<QAction *>() << actionType.action());
            }
            if (interface->plugin()->hasPopupMenuSupport()) {
                type = MessageComposer::PluginActionType::PopupMenu;
                lst = mActionHash.value(type);
                if (!lst.isEmpty()) {
                    QAction *act = new QAction(this);
                    act->setSeparator(true);
                    lst << act << actionType.action();
                    mActionHash.insert(type, lst);
                } else {
                    mActionHash.insert(type, QList<QAction *>() << actionType.action());
                }
            }
            if (interface->plugin()->hasToolBarSupport()) {
                type = MessageComposer::PluginActionType::ToolBar;
                lst = mActionHash.value(type);
                if (!lst.isEmpty()) {
                    QAction *act = new QAction(this);
                    act->setSeparator(true);
                    lst << act << actionType.action();
                    mActionHash.insert(type, lst);
                } else {
                    mActionHash.insert(type, QList<QAction *>() << actionType.action());
                }
            }
        }
    }
    return mActionHash;
}
