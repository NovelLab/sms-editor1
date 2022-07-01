#include "drafteditor.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
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
// TODO: なぜかcurrentitemがsaveされない問題
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
        file_title_->setText(data->DataOf(0).toString());
        pov_->setText(data->DataOf(4).toString());
        stage_->setText(data->DataOf(5).toString());
        date_->setText(data->DataOf(6).toString());
        time_->setText(data->DataOf(7).toString());
        synop_->setPlainText(data->DataOf(1).toString());
        note_->setPlainText(data->DataOf(3).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void DraftEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (pov_->isModified())
        current_item_->SetData(4, pov_->text());
    if (stage_->isModified())
        current_item_->SetData(5, stage_->text());
    if (date_->isModified())
        current_item_->SetData(6, date_->text());
    if (time_->isModified())
        current_item_->SetData(7, time_->text());
    if (synop_->document()->isModified())
        current_item_->SetData(1, synop_->toPlainText());
    if (note_->document()->isModified())
        current_item_->SetData(3, note_->toPlainText());
}

void DraftEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
