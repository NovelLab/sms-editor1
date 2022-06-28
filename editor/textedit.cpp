#include "textedit.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit{parent}
{

}

TextEdit::~TextEdit()
{
    delete current_item_;
}

// methods
void TextEdit::UpdateView(const QTreeWidgetItem *item)
{
    if (current_item_ && this->document()->isModified())
        SaveToCurrentItem_();

    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data) {
        this->setPlainText(data->DataOf(2).toString());
        current_item_ = data;
    }
}

// methods (private)
void TextEdit::SaveToCurrentItem_()
{
    if (!current_item_)
        return;

    current_item_->SetData(2, this->toPlainText());
}
