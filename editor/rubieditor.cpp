#include "rubieditor.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QDebug>

RubiEditor::RubiEditor(Ui::MainWindow *ui)
    : file_title_{ui->lblRubiTitle},
      keyword_{ui->lineRubiKeyword},
      converted_{ui->lineRubiConverted},
      always_{ui->checkRubiAlways},
      exclusions_{ui->lineRubiExclusions}
{
}

// methods
void RubiEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void RubiEditor::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(ItemKeys::Rubi::Name).toString());
        keyword_->setText(data->DataOf(ItemKeys::Rubi::Keyword).toString());
        converted_->setText(data->DataOf(ItemKeys::Rubi::Converted).toString());
        always_->setChecked(data->DataOf(ItemKeys::Rubi::Always).toBool());
        exclusions_->setText(data->DataOf(ItemKeys::Rubi::Exclusions).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void RubiEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (keyword_->isModified())
        current_item_->SetData(ItemKeys::Rubi::Keyword, keyword_->text());
    if (converted_->isModified())
        current_item_->SetData(ItemKeys::Rubi::Converted, converted_->text());
    if (exclusions_->isModified())
        current_item_->SetData(ItemKeys::Rubi::Exclusions, exclusions_->text());
    current_item_->SetData(ItemKeys::Rubi::Always, always_->isChecked());
}

void RubiEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}
