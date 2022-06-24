#include "itemdatawriter.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

static const int kIndexTitle = 0;
static const int kIndexInfo = 1;
static const int kIndexText = 2;
static const int kIndexNote = 3;

ItemDataWriter::ItemDataWriter()
{

}

// methods
bool ItemDataWriter::Write(ItemData *data, KeyCategory key, const QVariant &value)
{
    return Write_(data, DataType::Category, FileType::None, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyFolder key, const QVariant &value)
{
    return Write_(data, DataType::Folder, FileType::None, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyGeneral key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::General, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyDraft key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Draft, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyPlot key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Plot, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyStage key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Stage, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyPerson key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Person, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyItem key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Item, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyWord key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Word, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyResearch key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Research, static_cast<int>(key), value);
}

bool ItemDataWriter::Write(ItemData *data, KeyNote key, const QVariant &value)
{
    return Write_(data, DataType::File, FileType::Note, static_cast<int>(key), value);
}

bool ItemDataWriter::WriteNote(ItemData *data, const QVariant &value)
{
    if (!data)
        return false;
    if (data->TypeOf() != DataType::File)
        return false;

    data->SetData(kIndexNote, value);
    return true;
}

bool ItemDataWriter::WriteSynopsysOrInfo(ItemData *data, const QVariant &value)
{
    if (!data)
        return false;
    if (data->TypeOf() != DataType::File)
        return false;

    data->SetData(kIndexInfo, value);
    return true;
}

bool ItemDataWriter::WriteText(ItemData *data, const QVariant &value)
{
    if (!data)
        return false;
    if (data->TypeOf() != DataType::File)
        return false;

    data->SetData(kIndexText, value);
    return true;
}

bool ItemDataWriter::WriteTitleOrName(ItemData *data, const QVariant &value)
{
    if (!data)
        return false;

    data->SetData(kIndexTitle, value);
    return true;
}

// methods (private)
bool ItemDataWriter::Write_(ItemData *data, DataType type, FileType ftype, int column, const QVariant &value)
{
    if (!data)
        return false;

    if (type != data->TypeOf())
        return false;

    if (ftype != data->FileTypeOf())
        return false;

    if (column < 0 || column >= data->ColumnCount())
        return false;

    data->SetData(column, value);
    return true;
}
