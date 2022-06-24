#include "xmlwriter.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "views/outlineview.h"

#include "tools/itemdatareader.h"

#include <QDebug>

XmlWriter::XmlWriter(const OutlineView *view)
    : view_{view}
{
    xml_.setAutoFormatting(true);
}

// methods
bool XmlWriter::WriteFile(QIODevice *device)
{
    xml_.setDevice(device);

    xml_.writeStartDocument();

    xml_.writeStartElement("sms-data");
    xml_.writeAttribute("version", "1.0");

    for (int i = 0; i < view_->topLevelItemCount(); ++i) {
        WriteToplevelItem_(view_->topLevelItem(i));
    }

    xml_.writeEndDocument();
    return true;
}

// methods (private)
void XmlWriter::WriteToplevelItem_(const QTreeWidgetItem *item)
{
    if (item->text(0) == "General") {
        WriteGeneralData_(item);
    } else if (item->text(0) == "Draft") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Plot") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Persons") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Stages") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Items") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Words") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Research") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Notes") {
        WriteCategoryData_(item);
    } else if (item->text(0) == "Trash") {
        WriteCategoryData_(item);
    } else {
        // TODO: no tracking category or unknown item.
        return;
    }
}

void XmlWriter::WriteCategoryData_(const QTreeWidgetItem *item)
{
    Q_ASSERT(item);

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>()) {
        // TODO: warning
        return;
    }

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    ItemDataReader reader;

    xml_.writeStartElement("category");

    xml_.writeTextElement("title", reader.Read(data, KeyCategory::Title).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        WriteChildItem_(item->child(i));
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteChildItem_(const QTreeWidgetItem *item)
{
    Q_ASSERT(item);

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>()) {
        // TODO: warning
        return;
    }

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();

    DataType dtype = data->TypeOf();
    if (dtype == DataType::Folder) {
        WriteFolderData_(item);
    } else if (dtype == DataType::File) {
        WriteFileData_(item);
    } else {
        // TODO: warning
        return;
    }
}

void XmlWriter::WriteFileData_(const QTreeWidgetItem *item)
{
    Q_ASSERT(item);
    Q_ASSERT(item->data(0, Qt::UserRole).canConvert<ItemData*>());

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    ItemDataReader reader;

    xml_.writeStartElement("file");

    FileType ftype = data->FileTypeOf();
    switch (ftype) {
      case FileType::Draft:
        xml_.writeTextElement("type", "Draft");
        xml_.writeTextElement("title", reader.Read(data, KeyDraft::Title).toString());
        xml_.writeTextElement("synopsys", reader.Read(data, KeyDraft::Synopsys).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyDraft::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyDraft::Note).toString());
        break;
      case FileType::Plot:
        xml_.writeTextElement("type", "Plot");
        xml_.writeTextElement("title", reader.Read(data, KeyPlot::Title).toString());
        xml_.writeTextElement("synopsys", reader.Read(data, KeyPlot::Synopsys).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyPlot::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyPlot::Note).toString());
        break;
      case FileType::Person:
        xml_.writeTextElement("type", "Person");
        xml_.writeTextElement("name", reader.Read(data, KeyPerson::Name).toString());
        xml_.writeTextElement("info", reader.Read(data, KeyPerson::Info).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyPerson::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyPerson::Note).toString());
        xml_.writeTextElement("age", reader.Read(data, KeyPerson::Age).toString());
        xml_.writeTextElement("gender", reader.Read(data, KeyPerson::Gender).toString());
        xml_.writeTextElement("job", reader.Read(data, KeyPerson::Job).toString());
        break;
      case FileType::Stage:
        xml_.writeTextElement("type", "Stage");
        xml_.writeTextElement("name", reader.Read(data, KeyStage::Name).toString());
        xml_.writeTextElement("info", reader.Read(data, KeyStage::Info).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyStage::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyStage::Note).toString());
        break;
      case FileType::Item:
        xml_.writeTextElement("type", "Item");
        xml_.writeTextElement("name", reader.Read(data, KeyItem::Name).toString());
        xml_.writeTextElement("info", reader.Read(data, KeyItem::Info).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyItem::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyItem::Note).toString());
        xml_.writeTextElement("item-category", reader.Read(data, KeyItem::Category).toString());
        break;
      case FileType::Word:
        xml_.writeTextElement("type", "Word");
        xml_.writeTextElement("name", reader.Read(data, KeyWord::Name).toString());
        xml_.writeTextElement("info", reader.Read(data, KeyWord::Info).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyWord::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyWord::Note).toString());
        break;
      case FileType::Research:
        xml_.writeTextElement("type", "Research");
        xml_.writeTextElement("title", reader.Read(data, KeyResearch::Title).toString());
        xml_.writeTextElement("synopsys", reader.Read(data, KeyResearch::Synopsys).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyResearch::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyResearch::Note).toString());
        break;
      case FileType::Note:
        xml_.writeTextElement("type", "Note");
        xml_.writeTextElement("title", reader.Read(data, KeyNote::Title).toString());
        xml_.writeTextElement("synopsys", reader.Read(data, KeyNote::Synopsys).toString());
        xml_.writeTextElement("text", reader.Read(data, KeyNote::Text).toString());
        xml_.writeTextElement("note", reader.Read(data, KeyNote::Note).toString());
        break;
      default:
        break;
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteFolderData_(const QTreeWidgetItem *item)
{
    Q_ASSERT(item);
    Q_ASSERT(item->data(0, Qt::UserRole).canConvert<ItemData*>());

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    ItemDataReader reader;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", reader.Read(data, KeyFolder::Title).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        WriteChildItem_(item->child(i));
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteGeneralData_(const QTreeWidgetItem *item)
{
    Q_ASSERT(item && item->text(0) == "General");

    if (!item->data(0, Qt::UserRole).canConvert<ItemData*>()) {
        // TODO: warning
        return;
    }
    if (!item->data(1, Qt::UserRole).canConvert<ItemData*>()) {
        // TODO: warning
        return;
    }

    ItemData *data = item->data(0, Qt::UserRole).value<ItemData*>();
    ItemData *gdata = item->data(1, Qt::UserRole).value<ItemData*>();
    ItemDataReader reader;

    xml_.writeStartElement("category");

    xml_.writeTextElement("title", reader.Read(data, KeyCategory::Title).toString());
    xml_.writeTextElement("book-title", reader.Read(gdata, KeyGeneral::BookTitle).toString());
    xml_.writeTextElement("book-subtitle", reader.Read(gdata, KeyGeneral::BookSubtitle).toString());
    xml_.writeTextElement("book-series", reader.Read(gdata, KeyGeneral::BookSeries).toString());
    xml_.writeTextElement("book-volume", reader.Read(gdata, KeyGeneral::BookVolume).toString());
    xml_.writeTextElement("book-genre", reader.Read(gdata, KeyGeneral::BookGenre).toString());
    xml_.writeTextElement("book-license", reader.Read(gdata, KeyGeneral::BookLicense).toString());
    xml_.writeTextElement("author-name", reader.Read(gdata, KeyGeneral::AuthorName).toString());
    xml_.writeTextElement("author-email", reader.Read(gdata, KeyGeneral::AuthorEmail).toString());

    xml_.writeEndElement();
}
