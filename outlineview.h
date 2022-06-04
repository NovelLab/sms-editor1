#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QListView>

class OutlineView : public QListView
{
    Q_OBJECT
public:
    OutlineView(QWidget *parent = nullptr);
    ~OutlineView() override;
};

#endif // OUTLINEVIEW_H
