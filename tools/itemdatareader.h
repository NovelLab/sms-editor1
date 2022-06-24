#ifndef ITEMDATAREADER_H
#define ITEMDATAREADER_H

#include <QVariant>

class ItemData;

enum class DataType;
enum class FileType;
enum class KeyCategory;
enum class KeyFolder;
enum class KeyGeneral;
enum class KeyDraft;
enum class KeyPlot;
enum class KeyPerson;
enum class KeyStage;
enum class KeyItem;
enum class KeyWord;
enum class KeyResearch;
enum class KeyNote;

class ItemDataReader
{
public:
    explicit ItemDataReader();

    QVariant Read(ItemData *data, KeyCategory key) const;
    QVariant Read(ItemData *data, KeyFolder key) const;
    QVariant Read(ItemData *data, KeyGeneral key) const;
    QVariant Read(ItemData *data, KeyDraft key) const;
    QVariant Read(ItemData *data, KeyPlot key) const;
    QVariant Read(ItemData *data, KeyPerson key) const;
    QVariant Read(ItemData *data, KeyStage key) const;
    QVariant Read(ItemData *data, KeyItem key) const;
    QVariant Read(ItemData *data, KeyWord key) const;
    QVariant Read(ItemData *data, KeyResearch key) const;
    QVariant Read(ItemData *data, KeyNote key) const;

    QVariant ReadTitleOrName(ItemData *data) const;
    QVariant ReadSynopsysOrInfo(ItemData *data) const;
    QVariant ReadText(ItemData *data) const;
    QVariant ReadNote(ItemData *data) const;

private:
    QVariant Read_(ItemData *data, DataType type, FileType ftype, int column) const;
};


#endif // ITEMDATAREADER_H
