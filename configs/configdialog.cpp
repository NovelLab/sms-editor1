#include "configdialog.h"
#include "ui_configdialog.h"

#include "common/configenums.h"
#include "configs/configmodel.h"
#include "items/configitem.h"

#include <QColorDialog>

#include <QDebug>

ConfigDialog::ConfigDialog(ConfigModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog),
    model_{model}
{
    ui->setupUi(this);
    UpdateUI_();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

// slots
void ConfigDialog::on_cmbBoxUiFontFamily_currentFontChanged(const QFont &f)
{
    model_->SetData(Config::UI::FontFamily, f.toString());
}


void ConfigDialog::on_spinBoxUiFontSize_editingFinished()
{
    model_->SetData(Config::UI::FontSize, ui->spinBoxUiFontSize->value());
}


void ConfigDialog::on_btnUiFontColor_clicked()
{
    QColor color = QColorDialog::getColor(model_->DataOf(Config::UI::FontColor).toString(),
                                          this,
                                          "色選択",
                                          QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        model_->SetData(Config::UI::FontColor, color.name());
        UpdateUiFontColorButton_(color);
    }
}


// methods (private)
void ConfigDialog::UpdateUI_()
{
    // UI
    UpdateUiFontFamily_(model_->DataOf(Config::UI::FontFamily).toString());
    UpdateUiFontSize_(model_->DataOf(Config::UI::FontSize).toInt());
    UpdateUiFontColorButton_(QColor(model_->DataOf(Config::UI::FontColor).toString()));
}

void ConfigDialog::UpdateUiFontFamily_(const QString &value)
{
    ui->cmbBoxUiFontFamily->setCurrentFont(QFont(value));
}

void ConfigDialog::UpdateUiFontSize_(const int size)
{
    ui->spinBoxUiFontSize->setValue(size);
}

void ConfigDialog::UpdateUiFontColorButton_(const QColor &color)
{
    // label
    ui->btnUiFontColor->setText(color.name());
    // background color
    QString style = QString("background-color: %1").arg(color.name());
    ui->btnUiFontColor->setStyleSheet(style);
}
