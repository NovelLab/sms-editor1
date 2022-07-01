#ifndef DRAFTEDITOR_H
#define DRAFTEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QTextEdit;
class QTreeWidgetItem;

class TreeItem;

class DraftEditor
{
public:
    explicit DraftEditor(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);
    void SaveCurrentItem();

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);

    QLabel *file_title_;
    QLineEdit *pov_;
    QLineEdit *stage_;
    QLineEdit *date_;
    QLineEdit *time_;
    QTextEdit *synop_;
    QTextEdit *note_;

    TreeItem *current_item_;
};

#endif // DRAFTEDITOR_H
