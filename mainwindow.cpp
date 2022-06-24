#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "views/dataview.h"
#include "views/generalview.h"
#include "views/personview.h"
#include "views/plotview.h"
#include "views/maintabview.h"
#include "views/outlineview.h"

#include "editor/texteditor.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "models/datamodel.h"
#include "models/personmodel.h"
#include "models/plotmodel.h"

#include "tools/itemchecker.h"
#include "tools/datacounter.h"
#include "tools/novelbuilder.h"

#include "xmls/xmlreader.h"
#include "xmls/xmlwriter.h"

#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

static const QString kProjectPath = "PROJECT_PATH";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // settings
    settings_ = new QSettings(QSettings::IniFormat, QSettings::UserScope, "sms", "sms");
    settings_->setIniCodec(QTextCodec::codecForName("UTF-8"));

    // views
    outline_view_ = ui->outlineView;
    general_view_ = new GeneralView(ui);
    plot_view_ = ui->plotView;
    person_view_ = ui->personView;
    data_view_ = ui->dataView;
    tab_view_ = ui->tabView;
    editor_ = ui->textEdit;

    // models
    PlotModel *plot_model = new PlotModel();
    plot_view_->setModel(plot_model);

    PersonModel *person_model = new PersonModel();
    person_view_->setModel(person_model);

    DataModel *data_model = new DataModel();
    data_view_->setModel(data_model);

    // connects
    connect(plot_model, &PlotModel::UpdatedItemData, outline_view_, &OutlineView::UpdateItemData);
    connect(person_model, &PersonModel::UpdatedItemData, outline_view_, &OutlineView::UpdateItemData);
    connect(data_model, &DataModel::UpdatedItemData, outline_view_, &OutlineView::UpdateItemData);

    connect(outline_view_, &OutlineView::itemChanged, this, &MainWindow::OnTreeItemTitleChanged);
    connect(outline_view_, &OutlineView::currentItemChanged, this, &MainWindow::OnTreeItemChangedForSave);

    InitDefaultCategories_();
}

MainWindow::~MainWindow()
{
    delete general_view_;
    delete plot_view_;
    delete person_view_;
    delete data_view_;
    delete editor_;
    delete tab_view_;
    delete outline_view_;
    delete ui;
}

// slots
void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    settings_->setValue(kProjectPath, fileName);

    outline_view_->clear();

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("XmlStream Reader"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return;
    }

    XmlReader reader(outline_view_);
    if (!reader.Read(&file)) {
        QMessageBox::warning(this, tr("XmlStream Reader"),
                             tr("Parse error in file %1:\n\n%2")
                             .arg(QDir::toNativeSeparators(fileName),
                                  reader.ErrorString()));
    } else {
        DisplayGeneralView_(outline_view_->topLevelItem(0));
        statusBar()->showMessage(tr("File loaded"), 2000);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = settings_->value(kProjectPath).toString();
    if (filename.isEmpty()) {
        on_actionSave_As_triggered();
    } else {
        SaveFile_(filename);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    QDir::currentPath(),
                                                    tr("XML Files (*.xml);;All Files (*)"));

    SaveFile_(fileName);
}

void MainWindow::on_actionCompile_triggered()
{
    NovelBuilder builder;
    QTreeWidgetItem *draft_item = outline_view_->topLevelItem(1);
    if (!draft_item)
        return;

    if (builder.Build(draft_item)) {
        this->statusBar()->showMessage("Successfull Build!", 2000);
    }
}

void MainWindow::on_btnFolder_clicked()
{
    QTreeWidgetItem *cur_item = outline_view_->currentItem();
    if (!IsValidatedTreeItem_(cur_item))
        return;

    ItemChecker checker;

    if (checker.IsCategory(cur_item) || checker.IsFolder(cur_item)) {
        outline_view_->AddFolder(cur_item);
        DisplayFolderView_(cur_item);
    }
}

void MainWindow::on_btnAdd_clicked()
{
    QTreeWidgetItem *cur_item = outline_view_->currentItem();
    if (!IsValidatedTreeItem_(cur_item))
        return;

    ItemChecker checker;

    if (checker.IsCategory(cur_item) || checker.IsFolder(cur_item)) {
        FileType type = outline_view_->FileCategoryFrom(outline_view_->ToplevelParentFrom(cur_item));
        outline_view_->AddFile(type, cur_item);
        DisplayFolderView_(cur_item);
    }
}

void MainWindow::on_btnDel_clicked()
{
    QTreeWidgetItem *cur_item = outline_view_->currentItem();
    if (!IsValidatedTreeItem_(cur_item))
        return;

    ItemChecker checker;
    if (!checker.IsCategory(cur_item)) {
        QTreeWidgetItem *parent = outline_view_->ToplevelParentFrom(cur_item);
        outline_view_->RemoveItem(cur_item);
        DisplayFolderView_(parent);
    }
}

void MainWindow::on_lineTitle_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineSubtitle_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineSeries_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineVolume_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineGenre_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineLicense_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineAuthorname_editingFinished()
{
    UpdateGeneralData_();
}


void MainWindow::on_lineEmail_editingFinished()
{
    UpdateGeneralData_();
}

void MainWindow::OnTreeItemChangedForSave(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (!current || !previous)
        return;

    if (!previous->data(0, Qt::UserRole).canConvert<ItemData*>())
        return;

    UpdateGeneralData_();

    ItemData *pre_data = previous->data(0, Qt::UserRole).value<ItemData*>();
    if (pre_data->TypeOf() == DataType::File)
        UpdateEditorData_(previous);
}

void MainWindow::OnTreeItemTitleChanged(QTreeWidgetItem *item, int column)
{
    if (!item)
        return;

    if (column < 0 || column > 1)
        return;

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>())
        return;

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    data->SetData(column, item->text(column));
}

// private methods
void MainWindow::DisplayFileView_(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    tab_view_->ChangeEditor();
    SetupEditorData_(item);

    DisplayCharCounts(item);
}

void MainWindow::DisplayFolderView_(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    ItemChecker checker;
    QTreeWidgetItem *par = outline_view_->ToplevelParentFrom(item);
    QString title = par->text(0);

    if (title == "Draft"
            || title == "Plot"
            || title == "Research"
            || title == "Notes"
            || title == "Trash") {
        tab_view_->ChangePlotView();
        plot_view_->UpdateView(item);
    } else if (title == "Persons") {
        tab_view_->ChangePersonView();
        person_view_->UpdateView(item);
    } else {
        tab_view_->ChangeDataView();
        data_view_->UpdateView(item);
    }
    outline_view_->setCurrentItem(const_cast<QTreeWidgetItem*>(item));

    DisplayCharCounts(item);
}

void MainWindow::DisplayGeneralView_(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    tab_view_->ChangeGeneral();
    SetupGeneralData_();
}

void MainWindow::DisplayCharCounts(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>())
        return;

    DataCounter counter;
    this->statusBar()->showMessage(QString("Char(%1)").arg(counter.TextCount(item)));
}

void MainWindow::InitDefaultCategories_()
{
    outline_view_->AddRootCategory("General");
    outline_view_->AddRootCategory("Draft");
    outline_view_->AddRootCategory("Plot");
    outline_view_->AddRootCategory("Persons");
    outline_view_->AddRootCategory("Stages");
    outline_view_->AddRootCategory("Items");
    outline_view_->AddRootCategory("Words");
    outline_view_->AddRootCategory("Research");
    outline_view_->AddRootCategory("Notes");
    outline_view_->AddRootCategory("Trash");

    SetupGeneralData_();
}

bool MainWindow::IsValidatedTreeItem_(const QTreeWidgetItem *item)
{
    if (!item)
        return false;

    ItemChecker checker;
    if (checker.IsGenerel(item) || checker.IsTrash(item))
        return false;

    return true;
}

void MainWindow::SaveFile_(const QString &fname)
{
    if (fname.isEmpty())
        return;

    QString f_name = ValidatedFilename_(fname);

    QFile file(f_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Xml Stream"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(f_name),
                                  file.errorString()));
        return;
    }

    XmlWriter writer(outline_view_);
    if (writer.WriteFile(&file)) {
        statusBar()->showMessage(tr("File saved"), 2000);

        settings_->setValue(kProjectPath, f_name);
    }
}

void MainWindow::SetupEditorData_(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    if (item->data(0, Qt::UserRole).canConvert<ItemData*>()) {
        ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
        editor_->SetData(data);
    }
}

void MainWindow::SetupGeneralData_()
{
    QTreeWidgetItem *gen_item = outline_view_->topLevelItem(0);
    Q_ASSERT(gen_item);

    if (gen_item->data(0, Qt::UserRole).canConvert<ItemData*>()
            && gen_item->data(1, Qt::UserRole).canConvert<ItemData*>()) {
        ItemData *data = gen_item->data(1, Qt::UserRole).value<ItemData*>();
        general_view_->SetDataAll(data);
    }
}

void MainWindow::UpdateEditorData_(const QTreeWidgetItem *item)
{
    if (!item)
        return;

    if (item->data(0, Qt::UserRole).canConvert<ItemData*>()) {
        ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
        editor_->UpdateData(data);
    }
}

void MainWindow::UpdateGeneralData_()
{
    QTreeWidgetItem *gen_item = outline_view_->topLevelItem(0);
    Q_ASSERT(gen_item);

    if (gen_item->data(0, Qt::UserRole).canConvert<ItemData*>()
            && gen_item->data(1, Qt::UserRole).canConvert<ItemData*>()) {
        ItemData *data = gen_item->data(1, Qt::UserRole).value<ItemData*>();
        general_view_->UpdateDataAll(data);
    }
}

QString MainWindow::ValidatedFilename_(const QString &fname)
{
    if (fname.contains(".xml"))
        return fname;
    else
        return QString("%1.%2").arg(fname).arg("xml");
}

void MainWindow::on_outlineView_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if (!item)
        return;

    ItemChecker checker;
    if (checker.IsCategory(item)) {
        if (checker.IsGenerel(item)) {
            tab_view_->ChangeGeneral();
        } else {
            DisplayFolderView_(item);
        }
    } else if (checker.IsFolder(item)) {
        DisplayFolderView_(item);
    } else if (checker.IsFile(item)) {
        DisplayFileView_(item);
    }
}

