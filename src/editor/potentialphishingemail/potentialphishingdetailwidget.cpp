/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/
#include "potentialphishingdetailwidget.h"

#include <KConfigGroup>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <KSharedConfig>
#include <KLocalizedString>

PotentialPhishingDetailWidget::PotentialPhishingDetailWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *lab = new QLabel(i18n("Select email to put in whitelist:"), this);
    lab->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(lab);

    mListWidget = new QListWidget(this);
    mListWidget->setObjectName(QStringLiteral("list_widget"));
    mainLayout->addWidget(mListWidget);
}

PotentialPhishingDetailWidget::~PotentialPhishingDetailWidget()
{
}

void PotentialPhishingDetailWidget::fillList(const QStringList &lst)
{
    mListWidget->clear();
    QStringList emailsAdded;
    for (const QString &mail : lst) {
        if (!emailsAdded.contains(mail)) {
            QListWidgetItem *item = new QListWidgetItem(mListWidget);
            item->setCheckState(Qt::Unchecked);
            item->setText(mail);
            emailsAdded << mail;
        }
    }
}

void PotentialPhishingDetailWidget::save()
{
    KConfigGroup group(KSharedConfig::openConfig(), "PotentialPhishing");
    QStringList potentialPhishing = group.readEntry("whiteList", QStringList());
    bool emailsAdded = false;
    const int numberOfItem(mListWidget->count());
    for (int i = 0; i < numberOfItem; ++i) {
        QListWidgetItem *item = mListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            const QString email = item->text();
            if (!potentialPhishing.contains(email)) {
                potentialPhishing << email;
                emailsAdded = true;
            }
        }
    }
    if (emailsAdded) {
        group.writeEntry("whiteList", potentialPhishing);
    }
}
