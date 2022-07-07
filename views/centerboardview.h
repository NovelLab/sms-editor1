#ifndef CENTERBOARDVIEW_H
#define CENTERBOARDVIEW_H

#include <QTableView>

class QLabel;
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
    void SetHeaderShow(bool isShownHorizontal, bool isShownVertical);
    void SetTitleLabel(QLabel *label);

    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *title_label_;

    GeneralType::Category cat_;
};

#endif // CENTERBOARDVIEW_H
