#include "novelbuilder.h"

#include "ui_mainwindow.h"

#include "builder/formatter.h"
#include "builder/rubimaker.h"
#include "common/buildenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTextStream>

#include <QDebug>

NovelBuilder::NovelBuilder(const Ui::MainWindow *ui)
{
    draft_view_ = ui->draftTreeView;
    rubimaker_ = new RubiMaker(ui);
}

NovelBuilder::~NovelBuilder()
{
    delete rubimaker_;
}

// methods
bool NovelBuilder::Build(QIODevice *device, BuildType type, bool with_rubi)
{
    ItemUtility util;
    QStringList outputs;
    for (int i = 0; i < draft_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = draft_view_->topLevelItem(i);
        if (util.IsValidTreeWidgetItem(item)) {
            if (item->checkState(1) == Qt::Unchecked)
                continue;
            if (util.IsFolder(item)) {
                outputs << OutputStrsFromFolder(item);
            } else if (util.IsFile(item)) {
                outputs << OutputStrsFromFile(item);
            }
        }
    }
    if (outputs.isEmpty())
        return false;

    Formatter formatter;
    QStringList formatted = formatter.FormatByType(type, outputs);

    if (with_rubi) {
        formatted = rubimaker_->AddRubi(formatted);
    }

    QTextStream out(device);
    for (int i = 0; i < formatted.count(); ++i) {
        out << formatted.at(i);
    }
    device->close();
    return true;
}

// methods (private)
QStringList NovelBuilder::OutputStrsFromFile(const QTreeWidgetItem *item)
{
    ItemUtility util;
    QStringList outputs;
    if (util.IsValidTreeWidgetItem(item) && item->checkState(1) == Qt::Checked) {
        TreeItem *data = util.ItemFromTreeWidgetItem(item);
        outputs << data->DataOf(ItemKeys::Draft::Text).toString().split("\n");
    }
    return outputs;
}

QStringList NovelBuilder::OutputStrsFromFolder(const QTreeWidgetItem *item)
{
    ItemUtility util;
    QStringList outputs;
    for (int i = 0; i < item->childCount(); ++i) {
        if (item->checkState(1) == Qt::Unchecked)
            continue;
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
