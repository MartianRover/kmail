/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "identityaddvcarddialog.h"

#include <QComboBox>
#include <KLocalizedString>
#include <KSeparator>
#include <KUrlRequester>

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

IdentityAddVcardDialog::IdentityAddVcardDialog(const QStringList &shadowIdentities, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Create own vCard"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &IdentityAddVcardDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &IdentityAddVcardDialog::reject);
    setModal(true);

    QWidget *mainWidget = new QWidget(this);
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(buttonBox);

    QVBoxLayout *vlay = new QVBoxLayout(mainWidget);
    vlay->setContentsMargins(0, 0, 0, 0);

    mButtonGroup = new QButtonGroup(this);
    mButtonGroup->setObjectName(QStringLiteral("buttongroup"));

    // row 1: radio button
    QRadioButton *radio = new QRadioButton(i18n("&With empty fields"), this);
    radio->setChecked(true);
    vlay->addWidget(radio);
    mButtonGroup->addButton(radio, static_cast<int>(Empty));

    // row 2: radio button
    QRadioButton *fromExistingVCard = new QRadioButton(i18n("&From existing vCard"), this);
    vlay->addWidget(fromExistingVCard);
    mButtonGroup->addButton(fromExistingVCard, static_cast<int>(FromExistingVCard));

    // row 3: KUrlRequester
    QHBoxLayout *hlay = new QHBoxLayout(); // inherits spacing
    vlay->addLayout(hlay);

    mVCardPath = new KUrlRequester(this);
    mVCardPath->setObjectName(QStringLiteral("kurlrequester_vcardpath"));
    mVCardPath->setMimeTypeFilters({QStringLiteral("text/vcard"), QStringLiteral("all/allfiles")});

    mVCardPath->setMode(KFile::LocalOnly | KFile::File);
    QLabel *label = new QLabel(i18n("&vCard path:"), this);
    label->setBuddy(mVCardPath);
    label->setEnabled(false);
    mVCardPath->setEnabled(false);
    hlay->addWidget(label);
    hlay->addWidget(mVCardPath);

    connect(fromExistingVCard, &QRadioButton::toggled, label, &QLabel::setEnabled);
    connect(fromExistingVCard, &QRadioButton::toggled, mVCardPath, &KUrlRequester::setEnabled);

    // row 4: radio button
    QRadioButton *duplicateExistingVCard = new QRadioButton(i18n("&Duplicate existing vCard"), this);
    vlay->addWidget(duplicateExistingVCard);
    mButtonGroup->addButton(duplicateExistingVCard, static_cast<int>(ExistingEntry));

    // row 5: combobox with existing identities and label
    hlay = new QHBoxLayout(); // inherits spacing
    vlay->addLayout(hlay);
    mComboBox = new QComboBox(this);
    mComboBox->setObjectName(QStringLiteral("identity_combobox"));
    mComboBox->setEditable(false);

    mComboBox->addItems(shadowIdentities);
    mComboBox->setEnabled(false);
    label = new QLabel(i18n("&Existing identities:"), this);
    label->setBuddy(mComboBox);
    label->setEnabled(false);
    hlay->addWidget(label);
    hlay->addWidget(mComboBox, 1);

    vlay->addWidget(new KSeparator);
    vlay->addStretch(1);   // spacer

    // enable/disable combobox and label depending on the third radio
    // button's state:
    connect(duplicateExistingVCard, &QRadioButton::toggled, label, &QLabel::setEnabled);
    connect(duplicateExistingVCard, &QRadioButton::toggled, mComboBox, &QComboBox::setEnabled);
    resize(350, 130);
}

IdentityAddVcardDialog::~IdentityAddVcardDialog()
{
}

IdentityAddVcardDialog::DuplicateMode IdentityAddVcardDialog::duplicateMode() const
{
    const int id = mButtonGroup->checkedId();
    return static_cast<DuplicateMode>(id);
}

QString IdentityAddVcardDialog::duplicateVcardFromIdentity() const
{
    return mComboBox->currentText();
}

QUrl IdentityAddVcardDialog::existingVCard() const
{
    return mVCardPath->url();
}
