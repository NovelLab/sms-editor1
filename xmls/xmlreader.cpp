#include "xmlreader.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "views/outlineview.h"

#include "tools/itemdatawriter.h"

#include <QTreeWidgetItem>

#include <QDebug>

XmlReader::XmlReader(OutlineView *view)
    : view_{view}
{

}

// methods
QString XmlReader::ErrorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml_.errorString())
            .arg(xml_.lineNumber())
            .arg(xml_.columnNumber());
}

bool XmlReader::Read(QIODevice *device)
{
    xml_.setDevice(device);

    if (xml_.readNextStartElement()) {
        if (xml_.name() == "sms-data") {
            ReadXmlData_();
        }
    }

    return true;
}

// methods (private)
void XmlReader::ReadXmlData_()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "sms-data");

    while (!xml_.atEnd()) {
        xml_.readNextStartElement();

        if (xml_.name() == "category") {
            ReadCategory_(0);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadCategory_(QTreeWidgetItem *item)
{
    Q_UNUSED(item);
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "category");

    QTreeWidgetItem *itm = CreateRootItem_();

    ItemData *data = new ItemData(DataType::Category, FileType::None);
    itm->setData(0, Qt::UserRole, QVariant::fromValue(data));

    ItemDataWriter writer;
    QString title;
    ItemData *gdata = 0;

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            title = xml_.readElementText();
            itm->setText(0, title);
            writer.Write(data, KeyCategory::Title, title);
            if (title == "General") {
                gdata = new ItemData(DataType::File, FileType::General);
                itm->setData(1, Qt::UserRole, QVariant::fromValue(gdata));
            }
        } else if (xml_.name() == "folder") {
            ReadFolder_(itm);
        } else if (xml_.name() == "file") {
            ReadFile_(itm);
        } else if (title == "General") {
            if ("book-title" == xml_.name()) {
                writer.Write(gdata, KeyGeneral::BookTitle, xml_.readElementText());
            } else if (xml_.name() == "book-subtitle") {
                writer.Write(gdata, KeyGeneral::BookSubtitle, xml_.readElementText());
            } else if (xml_.name() == "book-series") {
                writer.Write(gdata, KeyGeneral::BookSeries, xml_.readElementText());
            } else if (xml_.name() == "book-volume") {
                writer.Write(gdata, KeyGeneral::BookVolume, xml_.readElementText());
            } else if (xml_.name() == "book-genre") {
                writer.Write(gdata, KeyGeneral::BookGenre, xml_.readElementText());
            } else if (xml_.name() == "book-license") {
                writer.Write(gdata, KeyGeneral::BookLicense, xml_.readElementText());
            } else if (xml_.name() == "author-name") {
                writer.Write(gdata, KeyGeneral::AuthorName, xml_.readElementText());
            } else if (xml_.name() == "author-email") {
                writer.Write(gdata, KeyGeneral::AuthorEmail, xml_.readElementText());
            }
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *itm = CreateChildItem_(item);

    ItemData *data = new ItemData(DataType::Folder, FileType::None);
    itm->setData(0, Qt::UserRole, QVariant::fromValue(data));

    ItemDataWriter writer;

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            itm->setText(0, title);
            writer.Write(data, KeyFolder::Title, title);
        } else if (xml_.name() == "folder") {
            ReadFolder_(itm);
        } else if (xml_.name() == "file") {
            ReadFile_(itm);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *itm = CreateChildItem_(item);

    ItemDataWriter writer;
    FileType ftype = FileType::None;
    ItemData *data = new ItemData(DataType::File, ftype);
    itm->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if ("type" == xml_.name()) {
            ftype = FileTypeFrom_(xml_.readElementText());
            data = new ItemData(DataType::File, ftype);
            itm->setData(0, Qt::UserRole, QVariant::fromValue(data));
        } else if (xml_.name() == "title" || xml_.name() == "name") {
            QString title = xml_.readElementText();
            itm->setText(0, title);
            writer.WriteTitleOrName(data, title);
        } else if (xml_.name() == "synopsys" || xml_.name() == "info") {
            writer.WriteSynopsysOrInfo(data, xml_.readElementText());
        } else if (xml_.name() == "text") {
            writer.WriteText(data, xml_.readElementText());
        } else if (xml_.name() == "note") {
            writer.WriteText(data, xml_.readElementText());
        } else if (xml_.name() == "age") {
            if (ftype == FileType::Person) {
                writer.Write(data, KeyPerson::Age, xml_.readElementText());
            }
        } else if (xml_.name() == "gender") {
            if (ftype == FileType::Person) {
                writer.Write(data, KeyPerson::Gender, xml_.readElementText());
            }
        } else if (xml_.name() == "job") {
            if (ftype == FileType::Person) {
                writer.Write(data, KeyPerson::Job, xml_.readElementText());
            }
        } else if (xml_.name() == "item-category") {
            if (ftype == FileType::Item) {
                writer.Write(data, KeyItem::Category, xml_.readElementText());
            }
        } else {
            xml_.skipCurrentElement();
        }
    }
}

QTreeWidgetItem* XmlReader::CreateRootItem_()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(view_);

    view_->addTopLevelItem(item);

    return item;
}

QTreeWidgetItem* XmlReader::CreateChildItem_(QTreeWidgetItem *item)
{
    Q_ASSERT(item);

    return new QTreeWidgetItem(item);
}

FileType XmlReader::FileTypeFrom_(const QString &type)
{
    if (type == "Draft") {
        return FileType::Draft;
    } else if (type == "Plot") {
        return FileType::Plot;
    } else if (type == "Person") {
        return FileType::Person;
    } else if (type == "Stage") {
        return FileType::Stage;
    } else if (type == "Item") {
        return FileType::Item;
    } else if (type == "Word") {
        return FileType::Word;
    } else if (type == "Research") {
        return FileType::Research;
    } else if (type == "Note") {
        return FileType::Note;
    } else {
        return FileType::None;
    }
}
