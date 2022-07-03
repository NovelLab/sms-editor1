#ifndef BOOKINFOEDITOR_H
#define BOOKINFOEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QTextEdit;
class QTreeWidgetItem;
class TreeItem;

class BookInfoEditor
{
public:
    explicit BookInfoEditor(Ui::MainWindow *ui);
    ~BookInfoEditor();

    void UpdateView();
    void SaveCurrentItem();
    void Clear();

    TreeItem* GetCurrentItem() const;

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);
    void SetDefaultData_();

    QLineEdit *title_;
    QLineEdit *subtitle_;
    QLineEdit *series_;
    QLineEdit *volume_;
    QLineEdit *genre_;
    QLineEdit *license_;
    QLineEdit *author_name_;
    QLineEdit *email_;
    QLineEdit *one_line_;
    QTextEdit *three_lines_;
    QTextEdit *abstract_;

    TreeItem *current_item_ = nullptr;
};

#endif // BOOKINFOEDITOR_H
