#include "xmlwriter.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"
#include "views/drafttree.h"
#include "views/plottree.h"

#include <QDebug>

XmlWriter::XmlWriter(const Ui::MainWindow *ui)
{
    draft_view_ = ui->draftTreeView;
    plot_view_ = ui->plotTreeView;
    xml_.setAutoFormatting(true);
}

// methods
bool XmlWriter::WriteFile(QIODevice *device)
{
    xml_.setDevice(device);

    xml_.writeStartDocument();

    xml_.writeStartElement("sms-data");
    xml_.writeAttribute("version", "1.0");

    // general

    // draft
    WriteDraft_();

    // plot
    WritePlot_();

    // persons

    // worlds

    // research

    // notes

    // rubi

    // trash

    xml_.writeEndDocument();
    return true;
}

// methods (private)
void XmlWriter::WriteDraftFile_(const QTreeWidgetItem *item)
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
    xml_.writeStartElement("category");
    xml_.writeTextElement("title", "draft");

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
    xml_.writeStartElement("category");
    xml_.writeTextElement("title", "plot");

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
