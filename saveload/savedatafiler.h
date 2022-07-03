#ifndef SAVEDATAFILER_H
#define SAVEDATAFILER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSettings;
class MainWindow;
class ViewChanger;

class SaveDataFiler: public QObject
{
public:
    explicit SaveDataFiler();

    bool OpenFile(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings);
    bool SaveFile(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings);
    bool SaveFileAs(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings);

    // TODO: view changer using for book-title etc.
    bool BuildToFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings);

private:
    bool SaveFile_(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings, const QString &filename);
    QString ValidatedFilename_(const QString &fname, const QString &ext);
};

#endif // SAVEDATAFILER_H
