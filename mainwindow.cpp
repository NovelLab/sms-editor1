#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outlinetree.h"
#include "notepaditem.h"

#include <QTreeWidgetItem>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // init ui
    initOutline();
    initMainTab();
    initGeneral();
    initDraft();

    // default
    setDefaultOutlineTree();
    setDefaultGeneralTab();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

// my methods
void MainWindow::displayCardView(QTreeWidgetItem *item)
{
    displayMainTab(CategoryType::kDraft);

    draftTable_->show();
    draftEdit_->hide();
}

void MainWindow::displayEditor(QTreeWidgetItem *item)
{
    displayMainTab(CategoryType::kDraft);

    draftTable_->hide();
    draftEdit_->show();

    NotepadItem *note = qvariant_cast<NotepadItem*>(item->data(0, Qt::UserRole));

    draftEdit_->setText(note->getText());
}

void MainWindow::displayMainTab(CategoryType type)
{
    int index = static_cast<int>(type);
    mainTab_->tabBar()->setCurrentIndex(index);
}

// init ui
void MainWindow::initDraft()
{
    // draft tab
    draftTable_ = ui_->draftTableView;
    draftEdit_ = ui_->textEdit;

    draftTable_->show();
    draftEdit_->hide();
}

void MainWindow::initGeneral()
{
    // general tab
    generalTitle_ = ui_->lineBook_title;
    generalSubtitle_ = ui_->lineBook_subtitle;
    generalSeries_ = ui_->lineBook_series;
    generalVolume_ = ui_->lineBook_volume;
    generalGenre_ = ui_->lineBook_genre;
    generalLicense_ = ui_->lineBook_license;
    generalAuthorName_ = ui_->lineAuthor_name;
    generalAuthorEmail_ = ui_->lineAuthor_email;
}

void MainWindow::initMainTab()
{
    // main tab
    mainTab_ = ui_->mainTabWidget;

    mainTab_->tabBar()->setCurrentIndex(0);
}

void MainWindow::initOutline()
{
    // outline tree view
    outlineTree_ = ui_->outlineTreeWidget;
}

// set default
void MainWindow::setDefaultGeneralTab()
{
    generalTitle_->setText("作品タイトル");
    generalSubtitle_->setText("サブタイトル");
    generalSeries_->setText("シリーズ名");
    generalVolume_->setText("第１巻");
    generalGenre_->setText("ジャンル");
    generalLicense_->setText("(C)20xx");
    generalAuthorName_->setText("作者名");
    generalAuthorEmail_->setText("email@address");
}

void MainWindow::setDefaultOutlineTree()
{
    outlineTree_->clear();

    outlineTree_->setDefaultCategory("General");
    outlineTree_->setDefaultCategory("Draft");
}

// slots
void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_btnFolder_clicked()
{
    outlineTree_->addNewFolder();
}

void MainWindow::on_btnAdd_clicked()
{
    outlineTree_->addNewNotepad();
}

void MainWindow::on_btnDel_clicked()
{
    outlineTree_->removeItem();
}

void MainWindow::on_outlineTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    ItemType type = outlineTree_->getItemType();

    switch (type) {
      case ItemType::kCategory:
        return displayMainTab(outlineTree_->getCategoryType());
      case ItemType::kFolder:
        return displayCardView(item);
      case ItemType::kNotepad:
        return displayEditor(item);
      default:
        return;
    }
}
