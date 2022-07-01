#include "savedatafiler.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "builder/novelbuilder.h"
#include "common/appsettings.h"
#include "xmls/xmlreader.h"
#include "xmls/xmlwriter.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include <QDebug>

static const QString kKeyProjectPath = AppSettings::kProjectPath;
static const QString kKeyBuildPath = AppSettings::kBuildPath;
static const QString kDefaultOutputFile = DefaultSettings::kBuildFilename;

SaveDataFiler::SaveDataFiler()
    : QObject{}
{

}

SaveDataFiler::~SaveDataFiler()
{

}

// methods
bool SaveDataFiler::BuildToFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings)
{
    // TODO: specific output file name
    QString fileName = kDefaultOutputFile;
    QString cur_dir = QDir::currentPath();
    QString build_dir = "build";
    QDir build_path(cur_dir);
    if (!build_path.exists(build_dir)) {
        build_path.mkdir(build_dir);
    }

    QString f_name = ValidatedFilename_(fileName, "md");
    QString build_fname = build_path.path() + "/" + build_dir + "/" + f_name;

    QFile file(build_fname);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(mwin, tr("Text Stream"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(build_fname),
                                  file.errorString()));
        return false;
    }

    NovelBuilder *builder = new NovelBuilder(ui);
    if (builder->Build(&file)) {
        settings->setValue(kKeyBuildPath, build_dir);
        settings->setValue(AppSettings::kBuildFilename, build_fname);
        return true;
    } else {
        return false;
    }
}

bool SaveDataFiler::OpenFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings)
{
    QString fileName = QFileDialog::getOpenFileName(mwin,
                                                    tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
        return false;

    settings->setValue(kKeyProjectPath, fileName);

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
    QString filename = settings->value(kKeyProjectPath).toString();
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

    QString f_name = ValidatedFilename_(filename, "xml");

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
        settings->setValue(kKeyProjectPath, f_name);
        return true;
    } else {
        return false;
    }
}

QString SaveDataFiler::ValidatedFilename_(const QString &fname, const QString &ext)
{
    if (fname.contains(QString(".%1").arg(ext)))
        return fname;
    else
        return QString("%1.%2").arg(fname).arg(ext);
}
