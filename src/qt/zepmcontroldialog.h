// Copyright (c) 2016-2019 The PIVX developers
// Copyright (c) 2019 The Extreme Private Masternode developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZEPMCONTROLDIALOG_H
#define ZEPMCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zepm/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZEpmControlDialog;
}

class CZEpmControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZEpmControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZEpmControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZEpmControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZEpmControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZEpmControlDialog(QWidget *parent);
    ~ZEpmControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZEpmControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZEpmControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZEPMCONTROLDIALOG_H
