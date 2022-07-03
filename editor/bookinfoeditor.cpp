#include "bookinfoeditor.h"

#include "ui_mainwindow.h"

#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

BookInfoEditor::BookInfoEditor(Ui::MainWindow *ui)
    : title_{ui->lineBookTitle},
      subtitle_{ui->lineBookSubtitle},
      series_{ui->lineBookSeries},
      volume_{ui->lineBookVolume},
      genre_{ui->lineBookGenre},
      license_{ui->lineBookLicense},
      author_name_{ui->lineAuthorName},
      email_{ui->lineAuthorEmail},
      one_line_{ui->lineOutline1line},
      three_lines_{ui->txtEdit3Lines},
      abstract_{ui->txtEditAbstract}
{
    current_item_ = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::BookInfo);
    SetDefaultData_();
    UpdateView();
}

BookInfoEditor::~BookInfoEditor()
{
    delete current_item_;
}

// methods
void BookInfoEditor::Clear()
{
    if (!current_item_)
        current_item_ = new TreeItem(GeneralType::ItemType::File, GeneralType::Category::BookInfo);
    SetDefaultData_();
}

TreeItem* BookInfoEditor::GetCurrentItem() const
{
    return current_item_;
}

void BookInfoEditor::SaveCurrentItem()
{
    if (current_item_)
        SaveCurrentItemInternal_();
}

void BookInfoEditor::UpdateView()
{
    TreeItem *data = current_item_;
    if (data) {
        title_->setText(data->DataOf(ItemKeys::BookInfo::Title).toString());
        subtitle_->setText(data->DataOf(ItemKeys::BookInfo::Subtitle).toString());
        series_->setText(data->DataOf(ItemKeys::BookInfo::Series).toString());
        volume_->setText(data->DataOf(ItemKeys::BookInfo::Volume).toString());
        genre_->setText(data->DataOf(ItemKeys::BookInfo::Genre).toString());
        license_->setText(data->DataOf(ItemKeys::BookInfo::License).toString());
        author_name_->setText(data->DataOf(ItemKeys::BookInfo::AuthorName).toString());
        email_->setText(data->DataOf(ItemKeys::BookInfo::Email).toString());
        one_line_->setText(data->DataOf(ItemKeys::BookInfo::OneLine).toString());
        three_lines_->setPlainText(data->DataOf(ItemKeys::BookInfo::ThreeLines).toString());
        abstract_->setPlainText(data->DataOf(ItemKeys::BookInfo::Abstract).toString());
        SetCurrentItem_(data);
    }
}

// methods (private)
void BookInfoEditor::SaveCurrentItemInternal_()
{
    if (!current_item_)
        return;

    if (title_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Title, title_->text());
    if (subtitle_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Subtitle, subtitle_->text());
    if (series_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Series, series_->text());
    if (volume_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Volume, volume_->text());
    if (genre_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Genre, genre_->text());
    if (license_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::License, license_->text());
    if (author_name_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::AuthorName, author_name_->text());
    if (email_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Email, email_->text());
    if (one_line_->isModified())
        current_item_->SetData(ItemKeys::BookInfo::OneLine, one_line_->text());
    if (three_lines_->document()->isModified())
        current_item_->SetData(ItemKeys::BookInfo::ThreeLines, three_lines_->toPlainText());
    if (abstract_->document()->isModified())
        current_item_->SetData(ItemKeys::BookInfo::Abstract, abstract_->toPlainText());
}

void BookInfoEditor::SetCurrentItem_(TreeItem *item)
{
    current_item_ = item;
}

void BookInfoEditor::SetDefaultData_()
{
    Q_ASSERT(current_item_);
    current_item_->SetData(ItemKeys::BookInfo::Title, "タイトル");
    current_item_->SetData(ItemKeys::BookInfo::Subtitle, "サブタイトル");
    current_item_->SetData(ItemKeys::BookInfo::Series, "シリーズ");
    current_item_->SetData(ItemKeys::BookInfo::Volume, "巻");
    current_item_->SetData(ItemKeys::BookInfo::Genre, "ジャンル");
    current_item_->SetData(ItemKeys::BookInfo::License, "ライセンス");
    current_item_->SetData(ItemKeys::BookInfo::AuthorName, "著者名");
    current_item_->SetData(ItemKeys::BookInfo::Email, "Eメール");
    current_item_->SetData(ItemKeys::BookInfo::OneLine, "１行説明");
    current_item_->SetData(ItemKeys::BookInfo::ThreeLines, "３行要約");
    current_item_->SetData(ItemKeys::BookInfo::Abstract, "作品梗概");
}
