#include "xmlwriter.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"
#include "views/drafttree.h"


#include <QDebug>

XmlWriter::XmlWriter(const Ui::MainWindow *ui)
{
    draft_view_ = ui->draftTreeView;
    xml_.setAutoFormatting(true);
}

// methods
bool XmlWriter::WriteFile(QIODevice *device)
{
    xml_.setDevice(device);

    xml_.writeStartDocument();

    xml_.writeStartElement("sms-data");
    xml_.writeAttribute("version", "1.0");

    // draft
    WriteDraft_();

    xml_.writeEndDocument();
    return true;
}

// methods (private)
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

void XmlWriter::WriteDraftFile_(const QTreeWidgetItem *item)
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

void XmlWriter::WriteDraftFolder_(const QTreeWidgetItem *item)
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
