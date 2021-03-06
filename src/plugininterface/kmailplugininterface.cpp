/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kmailplugininterface.h"
#include <kmmainwidget.h>
#include "kmail_debug.h"

KMailPluginInterface::KMailPluginInterface(QObject *parent)
    : PimCommon::PluginInterface(parent)
{
    setPluginName(QStringLiteral("kmail"));
    setPluginDirectory(QStringLiteral("kmail/mainview"));
}

KMailPluginInterface::~KMailPluginInterface()
{
}

KMailPluginInterface *KMailPluginInterface::self()
{
    static KMailPluginInterface s_self;
    return &s_self;
}

void KMailPluginInterface::setMainWidget(KMMainWidget *mainwindow)
{
    mMainWindow = mainwindow;
}

void KMailPluginInterface::initializeInterfaceRequires(PimCommon::AbstractGenericPluginInterface *abstractInterface)
{
    if (!mMainWindow) {
        qCCritical(KMAIL_LOG) << "mainwindows not defined";
        return;
    }
    PimCommon::GenericPluginInterface *interface = static_cast<PimCommon::GenericPluginInterface *>(abstractInterface);
    PimCommon::GenericPluginInterface::RequireTypes requires = interface->requires();
    if (requires & PimCommon::GenericPluginInterface::CurrentItems) {
        interface->setItems(mMainWindow->currentSelection());
    }
    if (requires & PimCommon::GenericPluginInterface::Items) {
        qCDebug(KMAIL_LOG) << "PimCommon::GenericPluginInterface::Items not implemented";
    }
    if (requires & PimCommon::GenericPluginInterface::CurrentCollection) {
        if (mMainWindow->currentCollection().isValid()) {
            interface->setCurrentCollection(mMainWindow->currentCollection());
        } else {
            qCDebug(KMAIL_LOG) << "Current Collection not defined";
        }
    }
    if (requires & PimCommon::GenericPluginInterface::Collections) {
        qCDebug(KMAIL_LOG) << "PimCommon::GenericPluginInterface::Collection not implemented";
    }
}
