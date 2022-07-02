#ifndef PERSONEDITOR_H
#define PERSONEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QTextEdit;
class QTreeWidgetItem;

class TreeItem;

class PersonEditor
{
public:
    explicit PersonEditor(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);
    void SaveCurrentItem();

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);

    QLabel *file_title_;
    QLineEdit *fullname_;
    QLineEdit *age_;
    QLineEdit *gender_;
    QLineEdit *job_;
    QLineEdit *appearance_;
    QTextEdit *info_;
    QTextEdit *note_;

    TreeItem *current_item_;
};

#endif // PERSONEDITOR_H
