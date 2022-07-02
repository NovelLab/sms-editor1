#include "novelbuilder.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTextStream>

NovelBuilder::NovelBuilder(const Ui::MainWindow *ui)
{
    draft_view_ = ui->draftTreeView;
}

// methods
bool NovelBuilder::Build(QIODevice *device)
{
    ItemUtility util;
    QStringList outputs;
    for (int i = 0; i < draft_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = draft_view_->topLevelItem(i);
        if (util.IsValidTreeWidgetItem(item)) {
            if (util.IsFolder(item)) {
                outputs << OutputStrsFromFolder(item);
            } else if (util.IsFile(item)) {
                outputs << OutputStrsFromFile(item);
            }
        }
    }
    if (outputs.isEmpty())
        return false;

    // TODO: format
    QTextStream out(device);
    for (int i = 0; i < outputs.count(); ++i) {
        out << outputs.at(i) << "\n";
    }
    device->close();
    return true;
}

// methods (private)
QStringList NovelBuilder::OutputStrsFromFile(const QTreeWidgetItem *item)
{
    ItemUtility util;
    QStringList outputs;
    if (util.IsValidTreeWidgetItem(item)) {
        TreeItem *data = util.ItemFromTreeWidgetItem(item);
        outputs << data->DataOf(ItemKeys::Draft::Text).toString();
    }
    return outputs;
}

QStringList NovelBuilder::OutputStrsFromFolder(const QTreeWidgetItem *item)
{
    ItemUtility util;
    QStringList outputs;
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsValidTreeWidgetItem(child)) {
            if (util.IsFolder(child)) {
                outputs << OutputStrsFromFolder(child);
            } else if (util.IsFile(child)) {
                outputs << OutputStrsFromFile(child);
            }
        }
    }
    return outputs;
}
