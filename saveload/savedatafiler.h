#ifndef SAVEDATAFILER_H
#define SAVEDATAFILER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSettings;
class MainWindow;

class SaveDataFiler: public QObject
{
public:
    explicit SaveDataFiler();

    bool OpenFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings);
};

#endif // SAVEDATAFILER_H
