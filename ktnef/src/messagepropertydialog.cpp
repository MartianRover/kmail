/*
  This file is part of KTnef.

  SPDX-FileCopyrightText: 2003 Michael Goffioul <kdeprint@swing.be>
  SPDX-FileCopyrightText: 2012 Allen Winter <winter@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
*/

#include "messagepropertydialog.h"
#include "attachpropertydialog.h"

#include <KTNEF/KTNEFMessage>

#include <KLocalizedString>
#include <KStandardGuiItem>

#include <QTreeWidget>
#include <KConfigGroup>
#include <KGuiItem>
#include <QDialogButtonBox>
#include <QPushButton>
#include <KSharedConfig>
#include <QHeaderView>

MessagePropertyDialog::MessagePropertyDialog(QWidget *parent, KTNEFMessage *msg)
    : QDialog(parent)
{
    mMessage = msg;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Message Properties"));
    mListView = new QTreeWidget(this);
    mainLayout->addWidget(mListView);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &MessagePropertyDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MessagePropertyDialog::reject);
    mainLayout->addWidget(buttonBox);
    QPushButton *user1Button = new QPushButton;
    buttonBox->addButton(user1Button, QDialogButtonBox::ActionRole);
    connect(user1Button, &QPushButton::clicked, this, &MessagePropertyDialog::slotSaveProperty);

    const QStringList headerLabels
        = (QStringList(i18nc("@title:column property name", "Name"))
           << i18nc("@title:column property value", "Value"));
    mListView->setHeaderLabels(headerLabels);
    mListView->setAllColumnsShowFocus(true);
    mListView->setWordWrap(true);
    mListView->setAllColumnsShowFocus(true);
    mListView->setRootIsDecorated(false);

    KGuiItem::assign(user1Button, KStandardGuiItem::save());
    AttachPropertyDialog::formatPropertySet(mMessage, mListView);
    readConfig();
}

MessagePropertyDialog::~MessagePropertyDialog()
{
    writeConfig();
}

void MessagePropertyDialog::slotSaveProperty()
{
    AttachPropertyDialog::saveProperty(mListView, mMessage, this);
}

void MessagePropertyDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MessagePropertyDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
    const QByteArray headerState = group.readEntry("HeaderState", QByteArray());
    if (!headerState.isEmpty()) {
        mListView->header()->restoreState(headerState);
    }
}

void MessagePropertyDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MessagePropertyDialog");
    group.writeEntry("Size", size());
    group.writeEntry("HeaderState", mListView->header()->saveState());
    group.sync();
}
