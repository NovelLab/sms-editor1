#include "textedit.h"

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

    ItemDataReader reader;

    this->setPlainText(reader.ReadText(data).toString());
}

void TextEdit::UpdateData(ItemData *data)
{
    if (!data)
        return;

    if (!this->document()->isModified())
        return;

    ItemDataWriter writer;
    writer.WriteText(data, this->toPlainText());
}
