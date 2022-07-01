#ifndef DRAFTSUBVIEW_H
#define DRAFTSUBVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QTextEdit;
class QTreeWidgetItem;

class DraftSubView
{
public:
    explicit DraftSubView(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);

private:
    QLabel *file_title_;
    QLineEdit *pov_;
    QLineEdit *stage_;
    QLineEdit *date_;
    QLineEdit *time_;
    QTextEdit *synop_;
    QTextEdit *note_;
};

#endif // DRAFTSUBVIEW_H
