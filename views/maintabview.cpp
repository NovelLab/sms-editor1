#include "maintabview.h"

static const int kIdxGeneral = 0;
static const int kIdxPlotView = 1;
static const int kIdxPersonView = 2;
static const int kIdxDataView = 3;
static const int kIdxEditor = 4;

MainTabView::MainTabView(QWidget *parent)
    : QTabWidget{parent}
{

}

MainTabView::~MainTabView()
{

}

// methods
void MainTabView::ChangeGeneral()
{
    this->setCurrentIndex(kIdxGeneral);
}

void MainTabView::ChangePlotView()
{
    this->setCurrentIndex(kIdxPlotView);
}

void MainTabView::ChangePersonView()
{
    this->setCurrentIndex(kIdxPersonView);
}

void MainTabView::ChangeDataView()
{
    this->setCurrentIndex(kIdxDataView);
}

void MainTabView::ChangeEditor()
{
    this->setCurrentIndex(kIdxEditor);
}
