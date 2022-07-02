#include "personeditor.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

PersonEditor::PersonEditor(Ui::MainWindow *ui)
    : file_title_{ui->lblPersonTitle},
      fullname_{ui->linePersonFullname},
      age_{ui->linePersonAge},
      gender_{ui->linePersonGender},
      job_{ui->linePersonJob},
      appearance_{ui->linePersonAppearance},
      info_{ui->txtEditPersonInfo},
      note_{ui->txtEditPersonNote}
{

}

// methods
void PersonEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void PersonEditor::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(ItemKeys::Person::Name).toString());
        fullname_->setText(data->DataOf(ItemKeys::Person::Fullname).toString());
        age_->setText(data->DataOf(ItemKeys::Person::Age).toString());
        job_->setText(data->DataOf(ItemKeys::Person::Job).toString());
        gender_->setText(data->DataOf(ItemKeys::Person::Gender).toString());
        appearance_->setText(data->DataOf(ItemKeys::Person::Appearance).toString());
        info_->setPlainText(data->DataOf(ItemKeys::Person::Info).toString());
        note_->setPlainText(data->DataOf(ItemKeys::Person::Note).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void PersonEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (fullname_->isModified())
        current_item_->SetData(ItemKeys::Person::Fullname, fullname_->text());
    if (age_->isModified())
        current_item_->SetData(ItemKeys::Person::Age, age_->text());
    if (gender_->isModified())
        current_item_->SetData(ItemKeys::Person::Gender, gender_->text());
    if (job_->isModified())
        current_item_->SetData(ItemKeys::Person::Job, job_->text());
    if (appearance_->isModified())
        current_item_->SetData(ItemKeys::Person::Appearance, appearance_->text());
    if (info_->document()->isModified())
        current_item_->SetData(ItemKeys::Person::Info, info_->toPlainText());
    if (note_->document()->isModified())
        current_item_->SetData(ItemKeys::Person::Note, note_->toPlainText());
}

void PersonEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
