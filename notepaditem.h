#ifndef NOTEPADITEM_H
#define NOTEPADITEM_H

#include <QObject>
#include <QString>

enum class ItemType;

class NotepadItem
{
public:
    explicit NotepadItem(const QString &title, ItemType type);
    ~NotepadItem();

    ItemType getType();
    QString getTitle();
    QString getText();

    void setTitle(const QString &title);
    void setText(const QString &text);

private:
    ItemType type_;
    QString title_;
    QString text_;
};

Q_DECLARE_METATYPE(NotepadItem*);

#endif // NOTEPADITEM_H
