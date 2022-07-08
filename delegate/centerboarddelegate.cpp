#include "centerboarddelegate.h"

#include <QPainter>

CenterBoardDelegate::CenterBoardDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

// overrides
void CenterBoardDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.row() < 0 || index.row() >= index.model()->rowCount())
        return;

    if (index.column() == 0) {
        QRect cardRect = option.rect;
        painter->fillRect(cardRect, Qt::white);
        painter->setPen(Qt::black);
        painter->drawRect(cardRect);
        painter->drawText(cardRect, Qt::AlignCenter, index.data().toString());
    }

    if (index.column() == 1) {
        QRect cardRect = option.rect;
        painter->fillRect(cardRect, Qt::yellow);
        painter->setPen(Qt::black);
        painter->drawRect(cardRect);
        painter->drawText(cardRect, Qt::AlignCenter, index.data().toString());
    }
    return;
}

