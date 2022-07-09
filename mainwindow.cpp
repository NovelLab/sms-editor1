#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common/appsettings.h"
#include "common/generalenums.h"
#include "common/itemkeys.h"
#include "configs/configdialog.h"
#include "configs/globalsetting.h"
#include "delegate/corkboarddelegate.h"
#include "editor/bookinfoeditor.h"
#include "editor/markdownhighlighter.h"
#include "items/countitem.h"
#include "models/tableitemmodel.h"
#include "saveload/savedatafiler.h"
#include "tools/counter.h"
#include "views/outlineview.h"
#include "views/viewchanger.h"

#include <QSettings>
#include <QString>
#include <QTextCodec>

#include <QDebug>

static const int kDefaultFontSize = DefaultSettings::kFontSize;
static const QString kProjectPath = AppSettings::kProjectPath;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // settings
    settings_ = new QSettings(QSettings::IniFormat, QSettings::UserScope, "sms", "sms");
    settings_->setIniCodec(QTextCodec::codecForName("UTF-8"));

    global_setting_ = new GlobalSetting();

    view_changer_ = new ViewChanger(ui);
    draft_tree_ = ui->draftTreeView;
    plot_tree_ = ui->plotTreeView;
    person_tree_ = ui->personTreeView;
    world_tree_ = ui->worldTreeView;
    research_tree_ = ui->researchTreeView;
    notes_tree_ = ui->notesTreeView;
    rubi_tree_ = ui->rubiTreeView;
    trash_tree_ = ui->trashTreeView;

    // set category
    draft_tree_->SetCategory(GeneralType::Category::Draft);
    plot_tree_->SetCategory(GeneralType::Category::Plot);
    person_tree_->SetCategory(GeneralType::Category::Persons);
    world_tree_->SetCategory(GeneralType::Category::Worlds);
    research_tree_->SetCategory(GeneralType::Category::Research);
    notes_tree_->SetCategory(GeneralType::Category::Notes);
    rubi_tree_->SetCategory(GeneralType::Category::Rubi);
    trash_tree_->SetCategory(GeneralType::Category::Trash);
    // set trash
    OutlineView::SetTrashBox(trash_tree_);

    // size settings
    ui->frameChanger->setMaximumWidth(120);
    ui->outlineTab->setMaximumWidth(200);
    ui->sideTab->setMaximumWidth(400);

    ui->outlineTab->tabBar()->hide();
    ui->mainViewTab->tabBar()->hide();
    ui->sideTab->tabBar()->hide();

#ifdef QT_DEBUG
    ui->outlineTab->tabBar()->show();
    ui->mainViewTab->tabBar()->show();
    ui->sideTab->tabBar()->show();
#endif

    // set category
    ui->corkboardView->SetCategory(GeneralType::Category::Draft);
    ui->personsTableView->SetCategory(GeneralType::Category::Persons);
    ui->worldsTableView->SetCategory(GeneralType::Category::Worlds);
    ui->rubiTableView->SetCategory(GeneralType::Category::Rubi);

    // set model
    TableItemModel *card_model = new TableItemModel(GeneralType::Category::Draft);
    ui->corkboardView->setModel(card_model);
    TableItemModel *persons_model = new TableItemModel(GeneralType::Category::Persons);
    ui->personsTableView->setModel(persons_model);
    TableItemModel *worlds_model = new TableItemModel(GeneralType::Category::Worlds);
    ui->worldsTableView->setModel(worlds_model);
    TableItemModel *rubi_model = new TableItemModel(GeneralType::Category::Rubi);
    ui->rubiTableView->setModel(rubi_model);

    // title label
    ui->corkboardView->SetTitleLabel(ui->lblCorkboardTitle);
    ui->personsTableView->SetTitleLabel(ui->lblPersonTableTitle);
    ui->worldsTableView->SetTitleLabel(ui->lblWorldTableTitle);
    ui->rubiTableView->SetTitleLabel(ui->lblRubiTableTitle);

    // header
    ui->personsTableView->SetHeaderShow(true, false);
    ui->worldsTableView->SetHeaderShow(true, false);
    ui->rubiTableView->SetHeaderShow(true, false);

    // delegate
    CorkBoardDelegate *center_delegate = new CorkBoardDelegate(ui->corkboardView);
    ui->corkboardView->setItemDelegate(center_delegate);

    // start view setting
    view_changer_->Change(GeneralType::Category::BookInfo);

    // setup editor
    MarkdownHighlighter *highlighter = new MarkdownHighlighter(ui->mainEditor->document());

    QFont font;
    font.setFamily("Takao");
    font.setFixedPitch(true);
    font.setPointSize(kDefaultFontSize);
    ui->mainEditor->setFont(font);
    highlighter->SetBaseFontSize(kDefaultFontSize);

    // connects
    connect(card_model, &TableItemModel::UpdatedItemData, ui->draftTreeView, &OutlineView::UpdateItemData);
    connect(card_model, &TableItemModel::UpdatedItemData, ui->plotTreeView, &OutlineView::UpdateItemData);
    connect(persons_model, &TableItemModel::UpdatedItemData, ui->personTreeView, &OutlineView::UpdateItemData);
    connect(worlds_model, &TableItemModel::UpdatedItemData, ui->worldTreeView, &OutlineView::UpdateItemData);
    connect(card_model, &TableItemModel::UpdatedItemData, ui->researchTreeView, &OutlineView::UpdateItemData);
    connect(card_model, &TableItemModel::UpdatedItemData, ui->notesTreeView, &OutlineView::UpdateItemData);
    connect(rubi_model, &TableItemModel::UpdatedItemData, ui->rubiTreeView, &OutlineView::UpdateItemData);

    // set default
    on_btnBookInfo_clicked();
    global_setting_->UpdateUi();
    ui->corkboardView->UpdateUi(settings_);
}

MainWindow::~MainWindow()
{
    delete view_changer_;
    delete draft_tree_;
    delete plot_tree_;
    delete person_tree_;
    delete world_tree_;
    delete research_tree_;
    delete notes_tree_;
    delete rubi_tree_;
    delete global_setting_;
    delete settings_;
    delete ui;
}

// slots (menu)
void MainWindow::on_actionClose_triggered()
{
    // NOTE: 先にBookInfoEditorにしないと、Treeでitemを選択している状態だとCrashする
    // TODO: すべてReadOnlyにしておく
    on_btnBookInfo_clicked();
    CloseProject_();
}

void MainWindow::on_actionCompile_triggered()
{
    SaveDataFiler filer;
    if (filer.BuildToFile(this, ui, settings_)) {
        this->statusBar()->showMessage("build successfull!", 2000);
    }
}

void MainWindow::on_actionNew_triggered()
{
    on_actionClose_triggered();
    on_actionSave_As_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    SaveDataFiler filer;
    if (filer.OpenFile(this, ui, view_changer_, settings_)) {
        view_changer_->Change(GeneralType::Category::BookInfo);
        this->statusBar()->showMessage("file loaded.", 2000);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionSave_triggered()
{
    SaveDataFiler filer;
    if (filer.SaveFile(this, ui, view_changer_, settings_)) {
        this->statusBar()->showMessage("file saved", 2000);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    SaveDataFiler filer;
    if (filer.SaveFileAs(this, ui, view_changer_, settings_)) {
        this->statusBar()->showMessage("file saved", 2000);
    }
}

// slots (changer buttons)
void MainWindow::on_btnBookInfo_clicked()
{
    view_changer_->Change(GeneralType::Category::BookInfo);
}

void MainWindow::on_btnDraft_clicked()
{
    view_changer_->Change(GeneralType::Category::Draft);
    view_changer_->Update(GeneralType::Category::Draft);
}

void MainWindow::on_btnNotes_clicked()
{
    view_changer_->Change(GeneralType::Category::Notes);
    view_changer_->Update(GeneralType::Category::Notes);
}

void MainWindow::on_btnPersons_clicked()
{
    view_changer_->Change(GeneralType::Category::Persons);
    view_changer_->Update(GeneralType::Category::Persons);
}

void MainWindow::on_btnPlot_clicked()
{
    view_changer_->Change(GeneralType::Category::Plot);
    view_changer_->Update(GeneralType::Category::Plot);
}

void MainWindow::on_btnResearch_clicked()
{
    view_changer_->Change(GeneralType::Category::Research);
    view_changer_->Update(GeneralType::Category::Research);
}

void MainWindow::on_btnRubi_clicked()
{
    view_changer_->Change(GeneralType::Category::Rubi);
    view_changer_->Update(GeneralType::Category::Rubi);
}

void MainWindow::on_btnTrash_clicked()
{
    view_changer_->Change(GeneralType::Category::Trash);
    view_changer_->Update(GeneralType::Category::Trash);
}

void MainWindow::on_btnWorlds_clicked()
{
    view_changer_->Change(GeneralType::Category::Worlds);
    view_changer_->Update(GeneralType::Category::Worlds);
}

// slots (draft tree)
void MainWindow::on_btnAddDraft_clicked()
{
    draft_tree_->AddFile(draft_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Draft);
}

void MainWindow::on_btnDelDraft_clicked()
{
    draft_tree_->RemoveToTrash(draft_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Draft);
}

void MainWindow::on_btnFolderDraft_clicked()
{
    draft_tree_->AddFolder(draft_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Draft);
}


void MainWindow::on_draftTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    //Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Draft);
    Counter counter;
    CountItem *item = counter.TextCharCountFrom(current);
    QString chars = QString("CHAR: %1(%2)").arg(item->DataOf(ItemKeys::Count::Full).toInt()).arg(item->DataOf(ItemKeys::Count::WhiteSpaces).toInt());
    this->statusBar()->showMessage(chars);
}

// slots (plot tree)
void MainWindow::on_plotTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Plot);
}

void MainWindow::on_btnFolderPlot_clicked()
{
    plot_tree_->AddFolder(plot_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Plot);
}


void MainWindow::on_btnAddPlot_clicked()
{
    plot_tree_->AddFile(plot_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Plot);
}


void MainWindow::on_btnDelPlot_clicked()
{
    plot_tree_->RemoveToTrash(plot_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Plot);
}

// slots (person tree)

void MainWindow::on_btnFolderPerson_clicked()
{
    person_tree_->AddFolder(person_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Persons);
}


void MainWindow::on_btnAddPerson_clicked()
{
    person_tree_->AddFile(person_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Persons);
}


void MainWindow::on_btnDelPerson_clicked()
{
    person_tree_->RemoveToTrash(person_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Persons);
}


void MainWindow::on_personTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Persons);
}

// slots (world tree)
void MainWindow::on_worldTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Worlds);
}


void MainWindow::on_btnFolderWorld_clicked()
{
    world_tree_->AddFolder(world_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Worlds);
}


void MainWindow::on_btnAddWorld_clicked()
{
    world_tree_->AddFile(world_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Worlds);
}


void MainWindow::on_btnDelWorld_clicked()
{
    world_tree_->RemoveToTrash(world_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Worlds);
}

// slots (research tree)
void MainWindow::on_researchTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Research);
}


void MainWindow::on_btnFolderResearch_clicked()
{
    research_tree_->AddFolder(research_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Research);
}


void MainWindow::on_btnAddResearch_clicked()
{
    research_tree_->AddFile(research_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Research);
}


void MainWindow::on_btnDelResearch_clicked()
{
    research_tree_->RemoveToTrash(research_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Research);
}

// slots (notes tree)
void MainWindow::on_notesTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Notes);
}


void MainWindow::on_btnFolderNotes_clicked()
{
    notes_tree_->AddFolder(notes_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Notes);
}


void MainWindow::on_btnAddNotes_clicked()
{
    notes_tree_->AddFile(notes_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Notes);
}


void MainWindow::on_btnDelNotes_clicked()
{
    notes_tree_->RemoveToTrash(notes_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Notes);
}

void MainWindow::on_rubiTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Rubi);
}


void MainWindow::on_btnFolderRubi_clicked()
{
    rubi_tree_->AddFolder(rubi_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Rubi);
}


void MainWindow::on_btnAddRubi_clicked()
{
    rubi_tree_->AddFile(rubi_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Rubi);
}


void MainWindow::on_btnDelRubi_clicked()
{
    rubi_tree_->RemoveToTrash(rubi_tree_->currentItem());
    view_changer_->Update(GeneralType::Category::Rubi);
}

// slots (trash)
void MainWindow::on_trashTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(GeneralType::Category::Trash);
}

void MainWindow::on_btnClearTrash_clicked()
{
    trash_tree_->ClearAllItems();
    view_changer_->Update(GeneralType::Category::Trash);
}

void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "(unimp) menu - Undo";
}


void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "(unimp) menu - Redo";
}


void MainWindow::on_actionCut_triggered()
{
    qDebug() << "(unimp) menu - Cut";
}


void MainWindow::on_actionCopy_triggered()
{
    qDebug() << "(unimp) menu - Copy";
}


void MainWindow::on_actionPaste_triggered()
{
    qDebug() << "(unimp) menu - Paste";
}


void MainWindow::on_actionPreference_triggered()
{
    ConfigDialog *conf = new ConfigDialog(global_setting_->GetModel(), this);
    bool result = conf->exec();
    if (result) {
        global_setting_->UpdateUi();
    }
}

// methods (private)
void MainWindow::CloseProject_()
{
    // tree
    draft_tree_->ClearAllItems();
    plot_tree_->ClearAllItems();
    person_tree_->ClearAllItems();
    world_tree_->ClearAllItems();
    research_tree_->ClearAllItems();
    notes_tree_->ClearAllItems();
    rubi_tree_->ClearAllItems();
    trash_tree_->ClearAllItems();
    // book info
    view_changer_->GetBookInfo()->Clear();
    // project settings
    settings_->setValue(AppSettings::kProjectPath, "");
}
