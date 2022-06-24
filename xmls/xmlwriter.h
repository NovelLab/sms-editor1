#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>

class OutlineView;
class QTreeWidgetItem;
class ItemData;

class XmlWriter
{
public:
    explicit XmlWriter(const OutlineView *view);
    bool WriteFile(QIODevice *device);

private:
    void WriteToplevelItem_(const QTreeWidgetItem *item);
    void WriteChildItem_(const QTreeWidgetItem *item);
    void WriteData_(const ItemData *data, const QString &type);

    void WriteCategoryData_(const QTreeWidgetItem *item);
    void WriteGeneralData_(const QTreeWidgetItem *item);
    void WriteFolderData_(const QTreeWidgetItem *item);
    void WriteFileData_(const QTreeWidgetItem *item);

    QXmlStreamWriter xml_;
    const OutlineView *view_;
};

#endif // XMLWRITER_H
