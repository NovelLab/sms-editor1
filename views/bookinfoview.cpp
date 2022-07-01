#include "bookinfoview.h"

#include "ui_mainwindow.h"

#include "enums/bookinfotypes.h"
#include "items/bookinfoitem.h"

static const QStringList kDefaultData = {
  "タイトル",
    "サブタイトル",
    "シリーズ",
    "巻",
    "ジャンル",
    "ライセンス",
    "著者名",
    "Eメール",
    "作品コピー",
    "三行で説明する",
    "作品梗概",
};

BookInfoView::BookInfoView(Ui::MainWindow *ui)
    : book_title_{ui->lineBookTitle},
      book_subtitle_{ui->lineBookSubtitle},
      book_series_{ui->lineBookSeries},
      book_volume_{ui->lineBookVolume},
      book_genre_{ui->lineBookGenre},
      book_license_{ui->lineBookLicense},
      author_name_{ui->lineAuthorName},
      author_email_{ui->lineAuthorEmail},
      outline_1line_{ui->lineOutline1line},
      outline_3lines_{ui->txtEdit3Lines},
      outline_abstract_{ui->txtEditAbstract}
{
    root_item_ = new BookInfoItem();

    Reset();
}

BookInfoView::~BookInfoView()
{
    delete root_item_;
}

// methods
void BookInfoView::Reset()
{
    for (int i = 0; i < kDefaultData.count(); ++i) {
        root_item_->SetData(i, kDefaultData.at(i));
    }
    UpdateView();
}

void BookInfoView::SaveData()
{
    if (book_title_->isModified())
        root_item_->SetData(0, book_title_->text());
    if (book_subtitle_->isModified())
        root_item_->SetData(1, book_subtitle_->text());
    if (book_series_->isModified())
        root_item_->SetData(2, book_series_->text());
    if (book_volume_->isModified())
        root_item_->SetData(3, book_volume_->text());
    if (book_genre_->isModified())
        root_item_->SetData(4, book_genre_->text());
    if (book_license_->isModified())
        root_item_->SetData(5, book_license_->text());
    if (author_name_->isModified())
        root_item_->SetData(6, author_name_->text());
    if (author_email_->isModified())
        root_item_->SetData(7, author_email_->text());
    if (outline_1line_->isModified())
        root_item_->SetData(8, outline_1line_->text());
    if (outline_3lines_->document()->isModified())
        root_item_->SetData(9, outline_3lines_->toPlainText());
    if (outline_abstract_->document()->isModified())
        root_item_->SetData(10, outline_abstract_->toPlainText());
}

void BookInfoView::UpdateView()
{
    book_title_->setText(root_item_->DataOf(0).toString());
    book_subtitle_->setText(root_item_->DataOf(1).toString());
    book_series_->setText(root_item_->DataOf(2).toString());
    book_volume_->setText(root_item_->DataOf(3).toString());
    book_genre_->setText(root_item_->DataOf(4).toString());
    book_license_->setText(root_item_->DataOf(5).toString());
    author_name_->setText(root_item_->DataOf(6).toString());
    author_email_->setText(root_item_->DataOf(7).toString());
    outline_1line_->setText(root_item_->DataOf(8).toString());
    outline_3lines_->setPlainText(root_item_->DataOf(9).toString());
    outline_abstract_->setPlainText(root_item_->DataOf(10).toString());
}
