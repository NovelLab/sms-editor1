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

    void SaveCurrentItem();
    void UpdateView(const QTreeWidgetItem *item, bool isReadonly = false);

private:
    void SaveToCurrentItem_();

    TreeItem *current_item_ = nullptr;
};

#endif // TEXTEDIT_H
