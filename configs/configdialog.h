#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class QColor;
class ConfigModel;

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(ConfigModel *model, QWidget *parent = nullptr);
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
    void UpdateUI_();
    //
    void UpdateUiFontFamily_(const QString &value);
    void UpdateUiFontSize_(const int size);
    void UpdateUiFontColorButton_(const QColor &color);

    Ui::ConfigDialog *ui;
    ConfigModel *model_;
};

#endif // CONFIGDIALOG_H
