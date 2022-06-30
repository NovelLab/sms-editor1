#ifndef NOTESTREE_H
#define NOTESTREE_H

#include "basetreeview.h"

class NotesTree : public BaseTreeView
{
    Q_OBJECT
public:
    explicit NotesTree(QWidget *parent = nullptr);
};

#endif // NOTESTREE_H
