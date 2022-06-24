#ifndef MAINTABVIEW_H
#define MAINTABVIEW_H

#include <QTabWidget>

class MainTabView : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabView(QWidget *parent = nullptr);
    ~MainTabView();

    void ChangeGeneral();
    void ChangePlotView();
    void ChangePersonView();
    void ChangeDataView();
    void ChangeEditor();
};

#endif // MAINTABVIEW_H
