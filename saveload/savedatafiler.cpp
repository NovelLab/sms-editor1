#include "savedatafiler.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "builder/novelbuilder.h"
#include "common/appsettings.h"
#include "common/buildenums.h"
#include "views/viewchanger.h"
#include "xmls/xmlreader.h"
#include "xmls/xmlwriter.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>

#include <QDebug>

SaveDataFiler::SaveDataFiler()
    : QObject{}
{

}

// methods
bool SaveDataFiler::BuildToFile(MainWindow *mwin, Ui::MainWindow *ui, QSettings *settings, BuildType type, bool with_rubi)
{
    // TODO: specific output file name
    QString fileName = settings->value(AppSettings::kBuildFilename).toString();
    QString cur_dir = settings->value(AppSettings::kProjectPath).toString();
    QString build_dir = settings->value(AppSettings::kBuildPath).toString();
    QDir build_path(cur_dir);
    if (!build_path.exists(build_dir)) {
        build_path.mkdir(build_dir);
    }

    QString f_name = ValidatedFilename_(fileName, settings->value(AppSettings::kBuildExtension).toString());
    QString build_fname = build_path.path() + QDir::separator() + build_dir + QDir::separator() + f_name;

    QFile file(build_fname);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(mwin, tr("Text Stream"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(build_fname),
                                  file.errorString()));
        return false;
    }

    NovelBuilder *builder = new NovelBuilder(ui);
    if (builder->Build(&file, type, with_rubi)) {
        settings->setValue(AppSettings::kBuildFilename, f_name);
        return true;
    } else {
        return false;
    }
}

bool SaveDataFiler::OpenFile(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings)
{
    QString fileName = QFileDialog::getOpenFileName(mwin,
                                                    tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
        return false;

    QFileInfo f(fileName);
    settings->setValue(AppSettings::kProjectPath, f.absolutePath());
    settings->setValue(AppSettings::kProjectFilename, f.fileName());

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(mwin, tr("XmlStream Reader"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

    XmlReader reader(ui, changer);
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

bool SaveDataFiler::SaveFile(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings)
{
    QString filename = settings->value(AppSettings::kProjectPath).toString() + QDir::separator() + settings->value(AppSettings::kProjectFilename).toString();
    if (filename.isEmpty()) {
        return SaveFileAs(mwin, ui, changer, settings);
    } else {
        return SaveFile_(mwin, ui, changer, settings, filename);
    }
}

bool SaveDataFiler::SaveFileAs(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings)
{
    QString fileName = QFileDialog::getSaveFileName(mwin,
                                                    tr("Save File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));

    return SaveFile_(mwin, ui, changer, settings, fileName);
}

// methods (private)
bool SaveDataFiler::SaveFile_(MainWindow *mwin, Ui::MainWindow *ui, ViewChanger *changer, QSettings *settings, const QString &filename)
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

    XmlWriter writer(ui, changer);
    if (writer.WriteFile(&file)) {
        QFileInfo f(f_name);
        settings->setValue(AppSettings::kProjectPath, f.absolutePath());
        settings->setValue(AppSettings::kProjectFilename, f.fileName());
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
