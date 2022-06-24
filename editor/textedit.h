#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class ItemData;

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);
    ~TextEdit();

    void SetData(ItemData *data);
    void UpdateData(ItemData *data);
};

#endif // TEXTEDIT_H
