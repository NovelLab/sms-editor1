#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>

class OutlineView;
class QTreeWidgetItem;

enum class FileType;

class XmlReader
{
public:
    explicit XmlReader(OutlineView *view);

    bool Read(QIODevice *device);
    QString ErrorString() const;

private:
    void ReadXmlData_();
    void ReadCategory_(QTreeWidgetItem *item);
    void ReadFolder_(QTreeWidgetItem *item);
    void ReadFile_(QTreeWidgetItem *item);

    QTreeWidgetItem* CreateRootItem_();
    QTreeWidgetItem* CreateChildItem_(QTreeWidgetItem *item);

    FileType FileTypeFrom_(const QString &type);

    QXmlStreamReader xml_;
    OutlineView *view_;
};


#endif // XMLREADER_H
