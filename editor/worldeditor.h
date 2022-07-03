#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QTextEdit;
class QTreeWidgetItem;

class TreeItem;

class WorldEditor
{
public:
    explicit WorldEditor(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);
    void SaveCurrentItem();

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);

    QLabel *file_title_;
    QLineEdit *division_;
    QTextEdit *info_;
    QTextEdit *note_;

    TreeItem *current_item_;
};

#endif // WORLDEDITOR_H
