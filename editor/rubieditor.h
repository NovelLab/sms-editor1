#ifndef RUBIEDITOR_H
#define RUBIEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QCheckBox;
class QTreeWidgetItem;

class TreeItem;

class RubiEditor
{
public:
    explicit RubiEditor(Ui::MainWindow *ui);

    void UpdateView(const QTreeWidgetItem *item);
    void SaveCurrentItem();

private:
    void SaveCurrentItemInternal_();
    void SetCurrentItem_(TreeItem *item);

    QLabel *file_title_;
    QLineEdit *keyword_;
    QLineEdit *converted_;
    QCheckBox *always_;
    QLineEdit *exclusions_;

    TreeItem *current_item_ = nullptr;
};

#endif // RUBIEDITOR_H
