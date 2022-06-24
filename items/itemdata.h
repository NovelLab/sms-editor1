#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QVector>
#include <QVariant>

enum class DataType;
enum class FileType;

static const int kDataSize = 8;

class ItemData
{
public:
    explicit ItemData(DataType type, FileType ftype, int size = kDataSize);
    ~ItemData();

    int ColumnCount() const;
    void SetData(int column, const QVariant &value);
    QVariant DataOf(int column) const;
    DataType TypeOf() const;
    FileType FileTypeOf() const;

private:
    bool ValidColumn_(int column) const;

    QVector<QVariant> values_;
    DataType type_;
    FileType file_type_;
};

Q_DECLARE_METATYPE(ItemData*);

#endif // ITEMDATA_H
