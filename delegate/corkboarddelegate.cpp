#include "corkboarddelegate.h"

#include "common/generalenums.h"
#include "items/treeitem.h"

#include <QLineEdit>
#include <QPainter>
#include <QPlainTextEdit>
#include <QTableView>

#include <QDebug>

CorkBoardDelegate::CorkBoardDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    parent_view_ = qobject_cast<QTableView*>(parent);
}

// overrides
QWidget* CorkBoardDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (index.column() == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setStyleSheet("background: white; color: black;");
        return editor;
    } else if (index.column() == 1 && item->TypeOf() == GeneralType::ItemType::File) {
        QPlainTextEdit *editor = new QPlainTextEdit(parent);
        editor->setFocusPolicy(Qt::StrongFocus);
        editor->setFrameShape(QFrame::NoFrame);
        editor->setPlaceholderText("Synopsys");
        editor->setStyleSheet("background: white; color: black;");
        return editor;
    } else {
        return nullptr;

    }
}

void CorkBoardDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.row() < 0 || index.row() >= index.model()->rowCount())
        return;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (index.column() == 0) {
        QRect cardRect = option.rect.adjusted(4,4,0,-4);
        painter->fillRect(cardRect, item->TypeOf() == GeneralType::ItemType::File ? Qt::white: Qt::lightGray);
        painter->setPen(Qt::black);
        painter->drawText(cardRect, Qt::AlignCenter, index.data().toString());
    }

    if (index.column() == 1 && item->TypeOf() == GeneralType::ItemType::File) {
        QRect cardRect = option.rect.adjusted(0,4,-4,-4);
        painter->fillRect(cardRect, Qt::white);
        painter->setPen(Qt::black);
        painter->drawText(cardRect.adjusted(10,10,-10,-10), Qt::AlignLeft, index.data().toString());
    }
    return;
}

QSize CorkBoardDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(parent_view_);
    int column = index.column();
    switch (column) {
      case 0:
        return QSize(200, 200);
      case 1:
        return QSize(parent_view_->width() - 200, 200);
      default:
        return QSize(100, 200);
    }
}
