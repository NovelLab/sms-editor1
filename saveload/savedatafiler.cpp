#include "savedatafiler.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common/appsettings.h"
#include "xmls/xmlreader.h"
#include "xmls/xmlwriter.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include <QDebug>

static const QString kProjectPath = AppSettings::kProjectPath;

SaveDataFiler::SaveDataFiler()
    : QObject{}
{

}

// methods*ui,
bool SaveDataFiler::OpenFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings)
{
    QString fileName = QFileDialog::getOpenFileName(mwin,
                                                    tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
        return false;

    settings->setValue(kProjectPath, fileName);

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(mwin, tr("XmlStream Reader"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

    XmlReader reader(ui);
    if (!reader.Read(&file)) {
        QMessageBox::warning(mwin, tr("XmlStream Reader"),
                             tr("Parse error in file %1:\n\n%2")
                             .arg(QDir::toNativeSeparators(fileName),
                                  reader.ErrorString()));
        return false;
    } else {
        return true;
    }
}
