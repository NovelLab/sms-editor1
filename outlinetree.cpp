#include "outlinetree.h"

#include <QDebug>

OutlineTree::OutlineTree(QWidget *parent)
    : QTreeWidget{parent}
{
    // constructor
}

OutlineTree::~OutlineTree()
{
    // destructor
}

// my methods
void OutlineTree::addNewFolder()
{
    qDebug() << "(unimplement) addNewFolder";
}

void OutlineTree::addNewNotepad()
{
    qDebug() << "(unimplement) addNewNotepad";
}

void OutlineTree::removeItem()
{
    qDebug() << "(unimplement) removeItem";
}
