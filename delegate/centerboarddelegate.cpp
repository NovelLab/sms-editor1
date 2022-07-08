#include "centerboarddelegate.h"

#include <QLineEdit>
#include <QPainter>
#include <QPlainTextEdit>
#include <QTableView>

#include <QDebug>

CenterBoardDelegate::CenterBoardDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    parent_view_ = qobject_cast<QTableView*>(parent);
}

// overrides
QWidget* CenterBoardDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    } else if (index.column() == 2) {
        // TODO: エンターで確定されないように工夫したエディタの実装
        QPlainTextEdit *editor = new QPlainTextEdit(parent);
        return editor;
    } else {
        return nullptr;
    }
}

void CenterBoardDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.row() < 0 || index.row() >= index.model()->rowCount())
        return;

    if (index.column() == 0) {
        QRect cardRect = option.rect.adjusted(4,4,0,-4);
        painter->fillRect(cardRect, Qt::white);
        painter->setPen(Qt::black);
        painter->drawRect(cardRect);
        painter->drawText(cardRect, Qt::AlignCenter, index.data().toString());
    }

    if (index.column() == 1) {
        QRect cardRect = option.rect.adjusted(0,4,-4,-4);
        painter->fillRect(cardRect, Qt::white);
        painter->setPen(Qt::black);
        painter->drawRect(cardRect);
        painter->drawText(cardRect.adjusted(10,10,-10,-10), Qt::AlignLeft, index.data().toString());
    }
    return;
}
