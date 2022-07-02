#include "ploteditor.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

PlotEditor::PlotEditor(Ui::MainWindow *ui)
    : file_title_{ui->lblPlotTitle},
      synop_{ui->txtEditSynopPlot},
      note_{ui->txtEditNotePlot}
{

}

// methods
void PlotEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void PlotEditor::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(ItemKeys::Plot::Title).toString());
        synop_->setPlainText(data->DataOf(ItemKeys::Plot::Synopsys).toString());
        note_->setPlainText(data->DataOf(ItemKeys::Plot::Note).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void PlotEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (synop_->document()->isModified())
        current_item_->SetData(ItemKeys::Plot::Synopsys, synop_->toPlainText());
    if (note_->document()->isModified())
        current_item_->SetData(ItemKeys::Plot::Note, note_->toPlainText());
}

void PlotEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
