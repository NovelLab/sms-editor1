#ifndef CENTERBOARDVIEW_H
#define CENTERBOARDVIEW_H

#include <QTableView>

class QTreeWidgetItem;

namespace GeneralType {
enum class Category;
}

class CenterBoardView : public QTableView
{
    Q_OBJECT
public:
    CenterBoardView(QWidget *parent = nullptr);

    void SetCategory(GeneralType::Category cat);

    void UpdateView(const QTreeWidgetItem *item);

private:
    GeneralType::Category cat_;
};

#endif // CENTERBOARDVIEW_H
