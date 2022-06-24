#include "personmodel.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"
#include "tools/itemdatawriter.h"

static const int kDisplayColumns = 5;

PersonModel::PersonModel(QObject *parent)
    : BaseViewModel{kDisplayColumns, parent}
{

}

// overrides
QVariant PersonModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    ItemData *data = ItemFrom_(index);

    if (!data)
        return QVariant();

    if (data->TypeOf() == DataType::Folder) {
        return DataFolderOf_(data, index.column());
    } else {
        return DataFileOf_(data, index.column());
    }
}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
{
    if (role != Qt::EditRole)
        return false;

    ItemData *data = ItemFrom_(index);
    if (!data)
        return false;

    bool result;

    if (data->TypeOf() == DataType::Folder) {
        result = SetFolderData_(data, index.column(), value);
    } else {
        result = SetFileData_(data, index.column(), value);
    }

    emit UpdatedItemData(index);

    return result;
}

// methods (priaevt)
QVariant PersonModel::DataFileOf_(ItemData *data, int column) const
{
    ItemDataReader reader;

    switch (column) {
      case 0:// Name
        return reader.Read(data, KeyPerson::Name);
      case 1:// Age
        return reader.Read(data, KeyPerson::Age);
      case 2:// Gender
        return reader.Read(data, KeyPerson::Gender);
      case 3:// Job
        return reader.Read(data, KeyPerson::Job);
      case 4:// info
        return reader.Read(data, KeyPerson::Info);
      default:
        return QVariant();
    }
}

QVariant PersonModel::DataFolderOf_(ItemData *data, int column) const
{
    ItemDataReader reader;

    switch (column) {
      case 0:// title
        return reader.Read(data, KeyFolder::Title);
      default:
        return QVariant();
    }
}

bool PersonModel::SetFileData_(ItemData *data, int column, const QVariant &value)
{
    ItemDataWriter writer;

    switch (column) {
      case 0:// name
        writer.Write(data, KeyPerson::Name, value);
        return true;
      case 1:// age
        writer.Write(data, KeyPerson::Age, value);
        return true;
      case 2:// gender
        writer.Write(data, KeyPerson::Gender, value);
        return true;
      case 3:// job
        writer.Write(data, KeyPerson::Job, value);
        return true;
      case 4:// info
        writer.Write(data, KeyPerson::Info, value);
        return true;
      default:
        return false;
    }
}

bool PersonModel::SetFolderData_(ItemData *data, int column, const QVariant &value)
{
    ItemDataWriter writer;

    switch (column) {
      case 0:// title
        writer.Write(data, KeyFolder::Title, value);
        return true;
      default:
        return false;
    }
}
