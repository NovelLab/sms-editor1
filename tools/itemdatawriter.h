#ifndef ITEMDATAWRITER_H
#define ITEMDATAWRITER_H

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

class ItemDataWriter
{
public:
    explicit ItemDataWriter();

    bool Write(ItemData *data, KeyCategory key, const QVariant &value);
    bool Write(ItemData *data, KeyFolder key, const QVariant &value);
    bool Write(ItemData *data, KeyGeneral key, const QVariant &value);
    bool Write(ItemData *data, KeyDraft key, const QVariant &value);
    bool Write(ItemData *data, KeyPlot key, const QVariant &value);
    bool Write(ItemData *data, KeyPerson key, const QVariant &value);
    bool Write(ItemData *data, KeyStage key, const QVariant &value);
    bool Write(ItemData *data, KeyItem key, const QVariant &value);
    bool Write(ItemData *data, KeyWord key, const QVariant &value);
    bool Write(ItemData *data, KeyResearch key, const QVariant &value);
    bool Write(ItemData *data, KeyNote key, const QVariant &value);

    bool WriteTitleOrName(ItemData *data, const QVariant &value);
    bool WriteSynopsysOrInfo(ItemData *data, const QVariant &value);
    bool WriteText(ItemData *data, const QVariant &value);
    bool WriteNote(ItemData *data, const QVariant &value);

private:
    bool Write_(ItemData *data, DataType type, FileType ftype, int column, const QVariant &value);
};


#endif // ITEMDATAWRITER_H
