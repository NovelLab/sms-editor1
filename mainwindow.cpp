#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common/appsettings.h"
#include "editor/markdownhighlighter.h"
#include "enums/generaltypes.h"
#include "models/cardmodel.h"
#include "saveload/savedatafiler.h"
#include "views/viewchanger.h"

#include <QSettings>
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

    view_changer_ = new ViewChanger(ui);
    draft_tree_ = ui->draftTreeView;

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

    // set model
    CardModel *card_model = new CardModel();
    ui->corkboardView->setModel(card_model);

    // start view setting
    view_changer_->Change(Category::BookInfo);

    // setup editor
    MarkdownHighlighter *highlighter = new MarkdownHighlighter(ui->mainEditor->document());

    QFont font;
    font.setFamily("Takao");
    font.setFixedPitch(true);
    font.setPointSize(kDefaultFontSize);
    ui->mainEditor->setFont(font);
    highlighter->SetBaseFontSize(kDefaultFontSize);

    // connects
    connect(card_model, &CardModel::UpdatedItemData, ui->draftTreeView, &DraftTree::UpdateItemData);
}

MainWindow::~MainWindow()
{
    delete view_changer_;
    delete draft_tree_;
    delete ui;
}

// slots (menu)
void MainWindow::on_actionClose_triggered()
{
    qDebug() << "(unimp) menu - Close";
}

void MainWindow::on_actionCompile_triggered()
{
    qDebug() << "(unimp) menu - Compile";
}

void MainWindow::on_actionNew_triggered()
{
    qDebug() << "(unimp) menu - New";
}

void MainWindow::on_actionOpen_triggered()
{
    SaveDataFiler filer;
    if (filer.OpenFile(this, ui, settings_)) {
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
    if (filer.SaveFile(this, ui, settings_)) {
        this->statusBar()->showMessage("file saved", 2000);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    SaveDataFiler filer;
    if (filer.SaveFileAs(this, ui, settings_)) {
        this->statusBar()->showMessage("file saved", 2000);
    }
}

// slots (changer buttons)
// TODO: update and saved each view data?
void MainWindow::on_btnBookInfo_clicked()
{
    view_changer_->Change(Category::BookInfo);
}

void MainWindow::on_btnDraft_clicked()
{
    view_changer_->Change(Category::Draft);
    view_changer_->Update(Category::Draft);
}

void MainWindow::on_btnNotes_clicked()
{
    view_changer_->Change(Category::Notes);
}

void MainWindow::on_btnPersons_clicked()
{
    view_changer_->Change(Category::Persons);
}

void MainWindow::on_btnPlot_clicked()
{
    view_changer_->Change(Category::Plot);
}

void MainWindow::on_btnResearch_clicked()
{
    view_changer_->Change(Category::Research);
}

void MainWindow::on_btnRubi_clicked()
{
    view_changer_->Change(Category::Rubi);
}

void MainWindow::on_btnTrash_clicked()
{
    view_changer_->Change(Category::Trash);
}

void MainWindow::on_btnWorlds_clicked()
{
    view_changer_->Change(Category::Worlds);
}

// slots (draft tree)
void MainWindow::on_btnAddDraft_clicked()
{
    draft_tree_->AddFile(draft_tree_->currentItem());
    view_changer_->Update(Category::Draft);
}

void MainWindow::on_btnDelDraft_clicked()
{
    draft_tree_->RemoveItem(draft_tree_->currentItem());
    view_changer_->Update(Category::Draft);
}

void MainWindow::on_btnFolderDraft_clicked()
{
    draft_tree_->AddFolder(draft_tree_->currentItem());
    view_changer_->Update(Category::Draft);
}


void MainWindow::on_draftTreeView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    view_changer_->Update(Category::Draft);
}


void MainWindow::on_lineBookTitle_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineBookSubtitle_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineBookSeries_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineBookVolume_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineBookGenre_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineBookLicense_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineOutline1line_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineAuthorName_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}


void MainWindow::on_lineAuthorEmail_editingFinished()
{
    view_changer_->Update(Category::BookInfo, true);
}
