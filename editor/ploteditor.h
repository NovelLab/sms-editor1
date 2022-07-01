#ifndef PLOTEDITOR_H
#define PLOTEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QTextEdit;
class QTreeWidgetItem;
class TreeItem;

class PlotEditor
{
public:
    explicit PlotEditor(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);
    void SaveCurrentItem();

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);

    QLabel *file_title_;
    QTextEdit *synop_;
    QTextEdit *note_;

    TreeItem *current_item_;
};

#endif // PLOTEDITOR_H
