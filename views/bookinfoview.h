#ifndef BOOKINFOVIEW_H
#define BOOKINFOVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QTextEdit;

class BookInfoItem;

class BookInfoView
{
public:
    explicit BookInfoView(Ui::MainWindow *ui);
    ~BookInfoView();

    void UpdateView();
    void Reset();

private:
    QLineEdit *book_title_;
    QLineEdit *book_subtitle_;
    QLineEdit *book_series_;
    QLineEdit *book_volume_;
    QLineEdit *book_genre_;
    QLineEdit *book_license_;

    QLineEdit *author_name_;
    QLineEdit *author_email_;

    QLineEdit *outline_1line_;
    QTextEdit *outline_3lines_;
    QTextEdit *outline_abstract_;

    BookInfoItem *root_item_;
};

#endif // BOOKINFOVIEW_H
