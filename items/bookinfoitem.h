#ifndef BOOKINFOITEM_H
#define BOOKINFOITEM_H

#include <QVariant>
#include <QVector>

class BookInfoItem
{
public:
    explicit BookInfoItem();
    ~BookInfoItem();

    QVariant DataOf(int column) const;
    bool SetData(int column, const QVariant &value);

    int ColumnCount() const;

private:
    bool IsValidColumn_(int column) const;

    QVector<QVariant> values_;
};

#endif // BOOKINFOITEM_H
