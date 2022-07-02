#include "drafteditor.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

DraftEditor::DraftEditor(Ui::MainWindow *ui)
    : file_title_{ui->lblDraftTitle},
      pov_{ui->linePOVDraft},
      stage_{ui->lineStageDraft},
      date_{ui->lineDateDraft},
      time_{ui->lineTimeDraft},
      synop_{ui->txtEditSynopDraft},
      note_{ui->txtEditNoteDraft}
{

}

// methods
void DraftEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void DraftEditor::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(ItemKeys::Draft::Title).toString());
        pov_->setText(data->DataOf(ItemKeys::Draft::POV).toString());
        stage_->setText(data->DataOf(ItemKeys::Draft::Stage).toString());
        date_->setText(data->DataOf(ItemKeys::Draft::Date).toString());
        time_->setText(data->DataOf(ItemKeys::Draft::Time).toString());
        synop_->setPlainText(data->DataOf(ItemKeys::Draft::Synopsys).toString());
        note_->setPlainText(data->DataOf(ItemKeys::Draft::Note).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void DraftEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (pov_->isModified())
        current_item_->SetData(ItemKeys::Draft::POV, pov_->text());
    if (stage_->isModified())
        current_item_->SetData(ItemKeys::Draft::Stage, stage_->text());
    if (date_->isModified())
        current_item_->SetData(ItemKeys::Draft::Date, date_->text());
    if (time_->isModified())
        current_item_->SetData(ItemKeys::Draft::Time, time_->text());
    if (synop_->document()->isModified())
        current_item_->SetData(ItemKeys::Draft::Synopsys, synop_->toPlainText());
    if (note_->document()->isModified())
        current_item_->SetData(ItemKeys::Draft::Note, note_->toPlainText());
}

void DraftEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
