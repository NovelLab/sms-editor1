#include "generalview.h"

#include "ui_mainwindow.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"
#include "tools/itemdatawriter.h"

GeneralView::GeneralView(Ui::MainWindow *ui)
    : book_title_{ui->lineTitle},
      book_subtitle_{ui->lineSubtitle},
      book_series_{ui->lineSeries},
      book_volume_{ui->lineVolume},
      book_genre_{ui->lineGenre},
      book_license_{ui->lineLicense},
      author_name_{ui->lineAuthorname},
      author_email_{ui->lineEmail}
{

}

GeneralView::~GeneralView()
{
    delete book_title_;
    delete book_subtitle_;
    delete book_series_;
    delete book_volume_;
    delete book_genre_;
    delete book_license_;
    delete author_name_;
    delete author_email_;
}

// methods
void GeneralView::SetDataAll(ItemData *data)
{
    if (!data)
        return;

    if (data->TypeOf() != DataType::File || data->FileTypeOf() != FileType::General)
        return;

    ItemDataReader reader;

    book_title_->setText(reader.Read(data, KeyGeneral::BookTitle).toString());
    book_subtitle_->setText(reader.Read(data, KeyGeneral::BookSubtitle).toString());
    book_series_->setText(reader.Read(data, KeyGeneral::BookSeries).toString());
    book_volume_->setText(reader.Read(data, KeyGeneral::BookVolume).toString());
    book_genre_->setText(reader.Read(data, KeyGeneral::BookGenre).toString());
    book_license_->setText(reader.Read(data, KeyGeneral::BookLicense).toString());
    author_name_->setText(reader.Read(data, KeyGeneral::AuthorName).toString());
    author_email_->setText(reader.Read(data, KeyGeneral::AuthorEmail).toString());
}

void GeneralView::UpdateDataAll(ItemData *data)
{
    if (!data)
        return;

    if (data->TypeOf() != DataType::File || data->FileTypeOf() != FileType::General)
        return;

    ItemDataWriter writer;

    writer.Write(data, KeyGeneral::BookTitle, book_title_->text());
    writer.Write(data, KeyGeneral::BookSubtitle, book_subtitle_->text());
    writer.Write(data, KeyGeneral::BookSeries, book_series_->text());
    writer.Write(data, KeyGeneral::BookVolume, book_volume_->text());
    writer.Write(data, KeyGeneral::BookGenre, book_genre_->text());
    writer.Write(data, KeyGeneral::BookLicense, book_license_->text());
    writer.Write(data, KeyGeneral::AuthorName, author_name_->text());
    writer.Write(data, KeyGeneral::AuthorEmail, author_email_->text());
}
