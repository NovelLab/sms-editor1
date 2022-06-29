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

SaveDataFiler::~SaveDataFiler()
{

}

// methods
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

bool SaveDataFiler::SaveFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings)
{
    QString filename = settings->value(kProjectPath).toString();
    if (filename.isEmpty()) {
        return SaveFileAs(mwin, ui, settings);
    } else {
        return SaveFile_(mwin, ui, settings, filename);
    }
}

bool SaveDataFiler::SaveFileAs(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings)
{
    QString fileName = QFileDialog::getSaveFileName(mwin,
                                                    tr("Save File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));

    return SaveFile_(mwin, ui, settings, fileName);
}

// methods (private)
bool SaveDataFiler::SaveFile_(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings, const QString &filename)
{
    if (filename.isEmpty())
        return false;

    QString f_name = ValidatedFilename_(filename);

    QFile file(f_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(mwin, tr("Xml Stream"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(f_name),
                                  file.errorString()));
        return false;
    }

    XmlWriter writer(ui);
    if (writer.WriteFile(&file)) {
        settings->setValue(kProjectPath, f_name);
        return true;
    } else {
        return false;
    }
}

QString SaveDataFiler::ValidatedFilename_(const QString &fname)
{
    if (fname.contains(".xml"))
        return fname;
    else
        return QString("%1.%2").arg(fname).arg("xml");
}
