#include "worldeditor.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

WorldEditor::WorldEditor(Ui::MainWindow *ui)
    : file_title_{ui->lblWorldTitle},
      division_{ui->lineWorldDivision},
      info_{ui->txtEditWorldInfo},
      note_{ui->txtEditWorldNote}
{

}

// methods
void WorldEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void WorldEditor::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(ItemKeys::World::Name).toString());
        division_->setText(data->DataOf(ItemKeys::World::Division).toString());
        info_->setPlainText(data->DataOf(ItemKeys::World::Info).toString());
        note_->setPlainText(data->DataOf(ItemKeys::World::Note).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void WorldEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (division_->isModified())
        current_item_->SetData(ItemKeys::World::Division, division_->text());
    if (info_->document()->isModified())
        current_item_->SetData(ItemKeys::World::Info, info_->toPlainText());
    if (note_->document()->isModified())
        current_item_->SetData(ItemKeys::World::Note, note_->toPlainText());
}

void WorldEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
