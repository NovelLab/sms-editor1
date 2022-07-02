#include "textedit.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit{parent}
{

}

// methods
void TextEdit::SaveCurrentItem()
{
    if (current_item_ && this->document()->isModified())
        SaveToCurrentItem_();
}

void TextEdit::UpdateView(const QTreeWidgetItem *item, bool isReadOnly)
{
    SaveCurrentItem();

    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data) {
        this->setPlainText(data->DataOf(ItemKeys::CommonKey::Text).toString());
        current_item_ = data;
        this->setReadOnly(isReadOnly);
    }
}

// methods (private)
void TextEdit::SaveToCurrentItem_()
{
    if (!current_item_)
        return;

    current_item_->SetData(ItemKeys::CommonKey::Text, this->toPlainText());
}
