#ifndef CORKBOARDVIEW_H
#define CORKBOARDVIEW_H

#include <QTableView>

class QLabel;
class QTreeWidgetItem;

class CorkboardView : public QTableView
{
    Q_OBJECT
public:
    explicit CorkboardView(QWidget *parent = nullptr);
    ~CorkboardView();

    void SetTitleLabel(QLabel *label);
    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *title_label_ = nullptr;
};

#endif // CORKBOARDVIEW_H
