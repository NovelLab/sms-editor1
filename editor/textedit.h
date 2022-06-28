#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class QTreeWidgetItem;

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);
    ~TextEdit();

    void UpdateView(const QTreeWidgetItem *item);
};

#endif // TEXTEDIT_H
