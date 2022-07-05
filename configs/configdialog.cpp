#include "configdialog.h"
#include "ui_configdialog.h"

#include "common/configenums.h"
#include "items/configitem.h"

#include <QColorDialog>

#include <QDebug>

ConfigDialog::ConfigDialog(ConfigItem *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog),
    current_item_{item}
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

// slots
void ConfigDialog::on_cmbBoxUiFontFamily_currentFontChanged(const QFont &f)
{
    qDebug() << "(unimp) combo box changed - font family";
}


void ConfigDialog::on_spinBoxUiFontSize_editingFinished()
{
    qDebug() << "(unimp) spin box finished - ui font size";
}


void ConfigDialog::on_btnUiFontColor_clicked()
{
    qDebug() << "(unimp) button ui font color";
    QColor color = QColorDialog::getColor("#FFFFFF", this, "色選択",
                                          QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        qDebug() << "(unimp) select color: " << color.name();
        ui->btnUiFontColor->setText(color.name());
        QString style = QString("background-color: %1").arg(color.name());
        ui->btnUiFontColor->setStyleSheet(style);
    }
}


// methods (private)
void ConfigDialog::SetDataFromItem_()
{
    // ui
}

