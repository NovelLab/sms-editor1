#include "rubimaker.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "views/outlineview.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

#include <QDebug>

RubiMaker::RubiMaker(const Ui::MainWindow *ui)
{
    items_.clear();
    InitRubiDB_(ui->rubiTreeView);
}

// methods
QStringList RubiMaker::AddRubi(const QStringList &data)
{
    QStringList rubi_outputs;
    QStringList discards;

    for (int i = 0; i < data.count(); ++i) {
        QString text = data.at(i);
        for (int j = 0; j < items_.count(); ++j) {
            TreeItem *data = items_.at(j);
            QString rubi = data->DataOf(ItemKeys::Rubi::Keyword).toString();
            if (discards.contains(rubi)) {
                continue;
            }
            QRegExp r(rubi);
            if (r.indexIn(text) > 0) {
                // match
                QString rep = data->DataOf(ItemKeys::Rubi::Converted).toString();
                if (rep.contains("\\1")) {
                    //
                    QString replaced = rep.replace("\\1", r.cap(1));
                    text.replace(r, replaced);
                } else {
                    text.replace(r, rep);
                }
                if (!data->DataOf(ItemKeys::Rubi::Always).toBool())
                    discards << rubi;
            }
        }
        rubi_outputs << text;
    }
    return rubi_outputs;
}

// methods (private)
void RubiMaker::InitRubiDB_(const OutlineView *view)
{
    ItemUtility utils;
    for (int i = 0; i < view->topLevelItemCount(); ++i) {
        QTreeWidgetItem *child = view->topLevelItem(i);
        if (utils.IsFolder(child)) {
            // folder
            InitRubiDBInFolder_(child);
        } else if (utils.IsFile(child)) {
            // file
            TreeItem *data = utils.ItemFromTreeWidgetItem(child);
            if (data)
                items_ << data;
        }
    }
    // TODO: []pattern must be used (): checking and alert.
}

void RubiMaker::InitRubiDBInFolder_(const QTreeWidgetItem *item)
{
    ItemUtility utils;
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (utils.IsFolder(child)) {
            // folder
            InitRubiDBInFolder_(child);
        } else if (utils.IsFile(child)) {
            // file
            TreeItem *data = utils.ItemFromTreeWidgetItem(child);
            if (data)
                items_ << data;
        }
    }
}
