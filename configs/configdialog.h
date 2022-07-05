#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigItem;

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(ConfigItem *item, QWidget *parent = nullptr);
    ~ConfigDialog();

private slots:
    void on_cmbBoxUiFontFamily_currentFontChanged(const QFont &f);
    void on_spinBoxUiFontSize_editingFinished();
    void on_btnUiFontColor_clicked();

private:
    enum class TabIndex {
        General,
        Project,
        Editor,
    };
    void SetDataFromItem_();

    Ui::ConfigDialog *ui;
    ConfigItem *current_item_;
};

#endif // CONFIGDIALOG_H
