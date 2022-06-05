#include "notepaditem.h"

#include "outlinetree.h"

NotepadItem::NotepadItem(const QString &title, ItemType type)
    : type_{type},
      title_{title},
      text_{"new text"}
{
    // constructor
}

NotepadItem::~NotepadItem()
{
    // destructor
}

// methods
QString NotepadItem::getText()
{
    return text_;
}

QString NotepadItem::getTitle()
{
    return title_;
}

ItemType NotepadItem::getType()
{
    return type_;
}

void NotepadItem::setText(const QString &text)
{
    text_ = text;
}

void NotepadItem::setTitle(const QString &title)
{
    title_ = title;
}
