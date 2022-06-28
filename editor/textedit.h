#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class QTreeWidgetItem;

class TreeItem;

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);
    ~TextEdit();

    void UpdateView(const QTreeWidgetItem *item);

private:
    void SaveToCurrentItem_();

    TreeItem *current_item_;
};

#endif // TEXTEDIT_H
