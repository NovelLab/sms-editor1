#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outlinetree.h"

#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

// init ui
void MainWindow::initDraft()
{
    // draft tab
    draftTable = ui->draftTableView;
    draftEdit = ui->textEdit;
}

void MainWindow::initGeneral()
{
    // general tab
    generalTitle = ui->lineBook_title;
    generalSubtitle = ui->lineBook_subtitle;
    generalSeries = ui->lineBook_series;
    generalVolume = ui->lineBook_volume;
    generalGenre = ui->lineBook_genre;
    generalLicense = ui->lineBook_license;
    generalAuthorName = ui->lineAuthor_name;
    generalAuthorEmail = ui->lineAuthor_email;
}

void MainWindow::initMainTab()
{
    // main tab
    mainTab = ui->mainTabWidget;

    mainTab->tabBar()->setCurrentIndex(0);
}

void MainWindow::initOutline()
{
    // outline tree view
    outlineTree = ui->outlineTreeWidget;
}

// set default
void MainWindow::setDefaultGeneralTab()
{
    generalTitle->setText("作品タイトル");
    generalSubtitle->setText("サブタイトル");
    generalSeries->setText("シリーズ名");
    generalVolume->setText("第１巻");
    generalGenre->setText("ジャンル");
    generalLicense->setText("(C)20xx");
    generalAuthorName->setText("作者名");
    generalAuthorEmail->setText("email@address");
}

void MainWindow::setDefaultOutlineTree()
{
    /*outlineTree->clear();

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setIcon(0, QIcon::fromTheme("folder"));
    item->setText(1, "TEST");
    outlineTree->addTopLevelItem(item);*/
}

// slots
void MainWindow::on_btnFolder_clicked()
{
    outlineTree->addNewFolder();
}
void MainWindow::on_btnAdd_clicked()
{
    outlineTree->addNewNotepad();
}


void MainWindow::on_btnDel_clicked()
{
    outlineTree->removeItem();
}

