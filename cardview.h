#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QTableView>

class CardView : public QTableView
{
    Q_OBJECT
public:
    explicit CardView(QWidget *parent = nullptr);
    ~CardView() override;
};

#endif // CARDVIEW_H
