#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QTreeView>

class OutlineView : public QTreeView
{
    Q_OBJECT
public:
    OutlineView(QWidget *parent = nullptr);
    ~OutlineView() override;
};

#endif // OUTLINEVIEW_H
