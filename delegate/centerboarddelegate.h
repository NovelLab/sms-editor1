#ifndef CENTERBOARDDELEGATE_H
#define CENTERBOARDDELEGATE_H

#include <QStyledItemDelegate>

class QTableView;

class CenterBoardDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CenterBoardDelegate(QObject *parent = nullptr);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QTableView *parent_view_;
};

#endif // CENTERBOARDDELEGATE_H
