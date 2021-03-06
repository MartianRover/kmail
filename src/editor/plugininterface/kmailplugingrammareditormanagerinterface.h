/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KMAILPLUGINGrammarEDITORMANAGERINTERFACE_H
#define KMAILPLUGINGrammarEDITORMANAGERINTERFACE_H

#include <QObject>
namespace KPIMTextEdit {
class RichTextComposer;
}
namespace PimCommon {
class CustomToolsWidgetNg;
}
class KActionCollection;
class KMailPluginGrammarEditorManagerInterface : public QObject
{
    Q_OBJECT
public:
    explicit KMailPluginGrammarEditorManagerInterface(QObject *parent = nullptr);
    ~KMailPluginGrammarEditorManagerInterface() = default;

    KPIMTextEdit::RichTextComposer *richTextEditor() const;
    void setRichTextEditor(KPIMTextEdit::RichTextComposer *richTextEditor);

    QWidget *parentWidget() const;
    void setParentWidget(QWidget *parentWidget);

    void initializePlugins();
    KActionCollection *actionCollection() const;
    void setActionCollection(KActionCollection *actionCollection);

    PimCommon::CustomToolsWidgetNg *customToolsWidget() const;
    void setCustomToolsWidget(PimCommon::CustomToolsWidgetNg *customToolsWidget);

private:
    Q_DISABLE_COPY(KMailPluginGrammarEditorManagerInterface)
    KPIMTextEdit::RichTextComposer *mRichTextEditor = nullptr;
    PimCommon::CustomToolsWidgetNg *mCustomToolsWidget = nullptr;
    QWidget *mParentWidget = nullptr;
    KActionCollection *mActionCollection = nullptr;
    bool mWasInitialized = false;
};

#endif // KMAILPLUGINGrammarEDITORMANAGERINTERFACE_H
