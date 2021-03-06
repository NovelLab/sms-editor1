#include "xmlwriter.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "editor/bookinfoeditor.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"
#include "views/outlineview.h"
#include "views/viewchanger.h"

#include <QDebug>

XmlWriter::XmlWriter(const Ui::MainWindow *ui, const ViewChanger *changer)
{
    draft_view_ = ui->draftTreeView;
    plot_view_ = ui->plotTreeView;
    persons_view_ = ui->personTreeView;
    worlds_view_ = ui->worldTreeView;
    research_view_ = ui->researchTreeView;
    notes_view_ = ui->notesTreeView;
    rubi_view_ = ui->rubiTreeView;
    trash_view_ = ui->trashTreeView;
    bookinfo_editor_ = changer->GetBookInfo();
    xml_.setAutoFormatting(true);
}

// methods
bool XmlWriter::WriteFile(QIODevice *device)
{
    xml_.setDevice(device);

    xml_.writeStartDocument();

    xml_.writeStartElement("sms-data");
    xml_.writeAttribute("version", "1.0");

    // book info
    WriteBookInfo_();

    // draft
    WriteDraft_();

    // plot
    WritePlot_();

    // persons
    WritePersons_();

    // worlds
    WriteWorlds_();

    // research
    WriteResearch_();

    // notes
    WriteNotes_();

    // rubi
    WriteRubis_();

    // trash
    WriteTrash_();

    xml_.writeEndDocument();
    return true;
}

// methods (private)
void XmlWriter::WriteBookInfo_()
{
    TreeItem *data = bookinfo_editor_->GetCurrentItem();
    if (!data)
        return;

    xml_.writeStartElement("category-bookinfo");

    for (int i = 0; i < ItemKeys::kBookInfoStrList.count(); ++i) {
        xml_.writeTextElement(ItemKeys::kBookInfoStrList.at(i).toLower(), data->DataOf(i).toString());
    }
    xml_.writeEndElement();
}

void XmlWriter::WriteDraftFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("build", QVariant(item->checkState(1)).toString());
    xml_.writeTextElement("synopsys", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());
    xml_.writeTextElement("pov", data->DataOf(4).toString());
    xml_.writeTextElement("stage", data->DataOf(5).toString());
    xml_.writeTextElement("date", data->DataOf(6).toString());
    xml_.writeTextElement("time", data->DataOf(7).toString());

    xml_.writeEndElement();
}

void XmlWriter::WriteDraftFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());
    xml_.writeTextElement("build", QVariant(item->checkState(1)).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteDraftFolder_(child);
        } else if (util.IsFile(child)) {
            WriteDraftFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteDraft_()
{
    xml_.writeStartElement("category-draft");

    ItemUtility util;

    for (int i = 0; i < draft_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = draft_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteDraftFolder_(item);
        } else if (util.IsFile(item)) {
            WriteDraftFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteNotesFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("synopsys", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());

    xml_.writeEndElement();
}

void XmlWriter::WriteNotesFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteNotesFolder_(child);
        } else if (util.IsFile(child)) {
            WriteNotesFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteNotes_()
{
    xml_.writeStartElement("category-notes");

    ItemUtility util;

    for (int i = 0; i < notes_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = notes_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteNotesFolder_(item);
        } else if (util.IsFile(item)) {
            WriteNotesFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WritePersonsFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("name", data->DataOf(0).toString());
    xml_.writeTextElement("info", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());
    xml_.writeTextElement("age", data->DataOf(4).toString());
    xml_.writeTextElement("gender", data->DataOf(5).toString());
    xml_.writeTextElement("job", data->DataOf(6).toString());
    xml_.writeTextElement("appearance", data->DataOf(7).toString());

    xml_.writeEndElement();
}

void XmlWriter::WritePersonsFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WritePersonsFolder_(child);
        } else if (util.IsFile(child)) {
            WritePersonsFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WritePersons_()
{
    xml_.writeStartElement("category-persons");

    ItemUtility util;

    for (int i = 0; i < persons_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = persons_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WritePersonsFolder_(item);
        } else if (util.IsFile(item)) {
            WritePersonsFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WritePlotFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("synopsys", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());

    xml_.writeEndElement();
}

void XmlWriter::WritePlotFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WritePlotFolder_(child);
        } else if (util.IsFile(child)) {
            WritePlotFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WritePlot_()
{
    xml_.writeStartElement("category-plot");

    ItemUtility util;

    for (int i = 0; i < plot_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = plot_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WritePlotFolder_(item);
        } else if (util.IsFile(item)) {
            WritePlotFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteResearchFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("synopsys", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());

    xml_.writeEndElement();
}

void XmlWriter::WriteResearchFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteResearchFolder_(child);
        } else if (util.IsFile(child)) {
            WriteResearchFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteResearch_()
{
    xml_.writeStartElement("category-research");

    ItemUtility util;

    for (int i = 0; i < research_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = research_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteResearchFolder_(item);
        } else if (util.IsFile(item)) {
            WriteResearchFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteRubisFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("name", data->DataOf(0).toString());
    xml_.writeTextElement("key", data->DataOf(1).toString());
    xml_.writeTextElement("converted", data->DataOf(2).toString());
    xml_.writeTextElement("always", data->DataOf(3).toString());
    xml_.writeTextElement("exclusions", data->DataOf(4).toString());

    xml_.writeEndElement();
}

void XmlWriter::WriteRubisFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteRubisFolder_(child);
        } else if (util.IsFile(child)) {
            WriteRubisFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteRubis_()
{
    xml_.writeStartElement("category-rubis");

    ItemUtility util;

    for (int i = 0; i < rubi_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = rubi_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteRubisFolder_(item);
        } else if (util.IsFile(item)) {
            WriteRubisFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteTrashFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    for (int i = 0; i < data->ColumnCount(); ++i) {
        xml_.writeTextElement(QString("data-%1").arg(i), data->DataOf(i).toString());
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteTrashFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteTrashFolder_(child);
        } else if (util.IsFile(child)) {
            WriteTrashFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteTrash_()
{
    xml_.writeStartElement("category-trashbox");

    ItemUtility util;

    for (int i = 0; i < trash_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = trash_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteTrashFolder_(item);
        } else if (util.IsFile(item)) {
            WriteTrashFile_(item);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteWorldsFile_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("file");

    xml_.writeTextElement("name", data->DataOf(0).toString());
    xml_.writeTextElement("info", data->DataOf(1).toString());
    xml_.writeTextElement("text", data->DataOf(2).toString());
    xml_.writeTextElement("note", data->DataOf(3).toString());
    xml_.writeTextElement("category", data->DataOf(4).toString());

    xml_.writeEndElement();
}

void XmlWriter::WriteWorldsFolder_(const QTreeWidgetItem *item)
{
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (!data)
        return;

    xml_.writeStartElement("folder");

    xml_.writeTextElement("title", data->DataOf(0).toString());
    xml_.writeTextElement("folding", QVariant(item->isExpanded()).toString());

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            WriteWorldsFolder_(child);
        } else if (util.IsFile(child)) {
            WriteWorldsFile_(child);
        }
    }

    xml_.writeEndElement();
}

void XmlWriter::WriteWorlds_()
{
    xml_.writeStartElement("category-worlds");

    ItemUtility util;

    for (int i = 0; i < worlds_view_->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = worlds_view_->topLevelItem(i);
        if (util.IsFolder(item)) {
            WriteWorldsFolder_(item);
        } else if (util.IsFile(item)) {
            WriteWorldsFile_(item);
        }
    }

    xml_.writeEndElement();
}

