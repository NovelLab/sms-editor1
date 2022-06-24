#include "texteditor.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"
#include "tools/itemdatawriter.h"

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit{parent}
{
}

TextEdit::~TextEdit()
{
}

// methods
void TextEdit::SetData(ItemData *data)
{
    if (!data)
        return;

    //ItemDataReader reader;

    this->setPlainText(data->Data(2).toString());
}

void TextEdit::UpdateData(ItemData *data)
{
    if (!data)
        return;

    if (!this->document()->isModified())
        return;

    //ItemDataWriter writer;
    data->SetData(2, this->toPlainText());
}
