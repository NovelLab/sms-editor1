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

}

// methods
void TextEdit::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data) {
        this->setPlainText(data->DataOf(2).toString());
    }
}

