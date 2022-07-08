#ifndef CORKBOARDDELEGATE_H
#define CORKBOARDDELEGATE_H

#include <QStyledItemDelegate>

class QTableView;

class CorkBoardDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CorkBoardDelegate(QObject *parent = nullptr);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QTableView *parent_view_;
};

#endif // CORKBOARDDELEGATE_H
