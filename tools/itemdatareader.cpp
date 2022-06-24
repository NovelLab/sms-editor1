#include "itemdatareader.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

static const int kIndexTitle = 0;
static const int kIndexInfo = 1;
static const int kIndexText = 2;
static const int kIndexNote = 3;

ItemDataReader::ItemDataReader()
{

}

QVariant ItemDataReader::Read(ItemData *data, KeyCategory key) const
{
    return Read_(data, DataType::Category, FileType::None, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyFolder key) const
{
    return Read_(data, DataType::Folder, FileType::None, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyGeneral key) const
{
    return Read_(data, DataType::File, FileType::General, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyDraft key) const
{
    return Read_(data, DataType::File, FileType::Draft, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyPlot key) const
{
    return Read_(data, DataType::File, FileType::Plot, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyPerson key) const
{
    return Read_(data, DataType::File, FileType::Person, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyStage key) const
{
    return Read_(data, DataType::File, FileType::Stage, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyItem key) const
{
    return Read_(data, DataType::File, FileType::Item, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyWord key) const
{
    return Read_(data, DataType::File, FileType::Word, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyResearch key) const
{
    return Read_(data, DataType::File, FileType::Research, static_cast<int>(key));
}

QVariant ItemDataReader::Read(ItemData *data, KeyNote key) const
{
    return Read_(data, DataType::File, FileType::Note, static_cast<int>(key));
}

QVariant ItemDataReader::ReadNote(ItemData *data) const
{
    if (!data)
        return QVariant();

    if (data->TypeOf() != DataType::File)
        return QVariant();

    return data->DataOf(kIndexNote);
}

QVariant ItemDataReader::ReadSynopsysOrInfo(ItemData *data) const
{
    if (!data)
        return QVariant();

    if (data->TypeOf() != DataType::File)
        return QVariant();

    return data->DataOf(kIndexInfo);
}

QVariant ItemDataReader::ReadText(ItemData *data) const
{
    if (!data)
        return QVariant();

    if (data->TypeOf() != DataType::File)
        return QVariant();

    return data->DataOf(kIndexText);
}

QVariant ItemDataReader::ReadTitleOrName(ItemData *data) const
{
    if (!data)
        return QVariant();

    return data->DataOf(kIndexTitle);
}

// private methods
QVariant ItemDataReader::Read_(ItemData *data, DataType type, FileType ftype, int column) const
{
    if (!data)
        return QVariant();

    if (type != data->TypeOf())
        return QVariant();

    if (ftype != data->FileTypeOf())
        return QVariant();

    if (column < 0 || column >= data->ColumnCount())
        return QVariant();

    return data->DataOf(column);
}
