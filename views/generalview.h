#ifndef GENERALVIEW_H
#define GENERALVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class ItemData;

class GeneralView
{
public:
    explicit GeneralView(Ui::MainWindow *ui);
    ~GeneralView();

    void UpdateDataAll(ItemData *data);
    void SetDataAll(ItemData *data);

private:
    QLineEdit *book_title_;
    QLineEdit *book_subtitle_;
    QLineEdit *book_series_;
    QLineEdit *book_volume_;
    QLineEdit *book_genre_;
    QLineEdit *book_license_;
    QLineEdit *author_name_;
    QLineEdit *author_email_;
};

#endif // GENERALVIEW_H
