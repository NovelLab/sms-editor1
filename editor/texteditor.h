#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

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

#endif // TEXTEDITOR_H
