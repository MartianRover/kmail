/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendlaterconfiguredialog.h"
#include "sendlaterconfigurewidget.h"
#include "kmail-version.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KHelpMenu>
#include <QMenu>
#include <KAboutData>
#include <QIcon>
#include <QDialogButtonBox>
#include <QApplication>

SendLaterConfigureDialog::SendLaterConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure"));
    setWindowIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SendLaterConfigureDialog::reject);

    mWidget = new SendLaterWidget(this);
    mWidget->setObjectName(QStringLiteral("sendlaterwidget"));
    connect(mWidget, &SendLaterWidget::sendNow, this, &SendLaterConfigureDialog::sendNow);
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttonBox);
    connect(okButton, &QPushButton::clicked, this, &SendLaterConfigureDialog::slotSave);

    readConfig();

    KAboutData aboutData = KAboutData(
        QStringLiteral("sendlateragent"),
        i18n("Send Later Agent"),
        QStringLiteral(KDEPIM_VERSION),
        i18n("Send emails later agent."),
        KAboutLicense::GPL_V2,
        i18n("Copyright (C) 2013-2020 Laurent Montel"));

    aboutData.addAuthor(i18n("Laurent Montel"),
                        i18n("Maintainer"), QStringLiteral("montel@kde.org"));

    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"),
                            i18nc("EMAIL OF TRANSLATORS", "Your emails"));

    KHelpMenu *helpMenu = new KHelpMenu(this, aboutData, true);
    //Initialize menu
    QMenu *menu = helpMenu->menu();
    helpMenu->action(KHelpMenu::menuAboutApp)->setIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    buttonBox->button(QDialogButtonBox::Help)->setMenu(menu);
}

SendLaterConfigureDialog::~SendLaterConfigureDialog()
{
    writeConfig();
}

QVector<Akonadi::Item::Id> SendLaterConfigureDialog::messagesToRemove() const
{
    return mWidget->messagesToRemove();
}

void SendLaterConfigureDialog::slotSave()
{
    mWidget->save();
    accept();
}

void SendLaterConfigureDialog::slotNeedToReloadConfig()
{
    mWidget->needToReload();
}

void SendLaterConfigureDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SendLaterConfigureDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
    mWidget->restoreTreeWidgetHeader(group.readEntry("HeaderState", QByteArray()));
}

void SendLaterConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SendLaterConfigureDialog");
    group.writeEntry("Size", size());
    mWidget->saveTreeWidgetHeader(group);
}
