#ifndef RUBITABLEVIEW_H
#define RUBITABLEVIEW_H

#include <QTableView>

class QLabel;
class QTreeWidgetItem;

class RubiTableView : public QTableView
{
    Q_OBJECT
public:
    explicit RubiTableView(QWidget *parent = nullptr);

    void SetTitleLabel(QLabel *label);
    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *title_label_ = nullptr;
};

#endif // RUBITABLEVIEW_H
