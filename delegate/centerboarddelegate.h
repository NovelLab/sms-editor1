#ifndef CENTERBOARDDELEGATE_H
#define CENTERBOARDDELEGATE_H

#include <QStyledItemDelegate>

class CenterBoardDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CenterBoardDelegate(QObject *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CENTERBOARDDELEGATE_H
