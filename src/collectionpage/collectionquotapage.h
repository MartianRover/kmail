/*
 *
 * SPDX-FileCopyrightText: 2006 Till Adam <adam@kde.org>
 * SPDX-FileCopyrightText: 2009-2020 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef COLLECTIONQUOTAPAGE_H
#define COLLECTIONQUOTAPAGE_H
#include <AkonadiWidgets/collectionpropertiespage.h>

class CollectionQuotaWidget;

/**
 * "Quota" tab in the folder dialog
 */
class CollectionQuotaPage : public Akonadi::CollectionPropertiesPage
{
    Q_OBJECT
public:
    explicit CollectionQuotaPage(QWidget *parent = nullptr);
    void load(const Akonadi::Collection &col) override;
    void save(Akonadi::Collection &col) override;
    Q_REQUIRED_RESULT bool canHandle(const Akonadi::Collection &collection) const override;

private:
    void init();
    CollectionQuotaWidget *mQuotaWidget = nullptr;
};

AKONADI_COLLECTION_PROPERTIES_PAGE_FACTORY(CollectionQuotaPageFactory, CollectionQuotaPage)

#endif /* COLLECTIONQUOTAPAGE_H */
