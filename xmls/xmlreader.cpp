#include "xmlreader.h"

#include "ui_mainwindow.h"

#include "common/itemkeys.h"
#include "editor/bookinfoeditor.h"
#include "items/treeitem.h"
#include "views/drafttree.h"
#include "views/viewchanger.h"
#include "utils/itemutility.h"

#include <QDebug>

XmlReader::XmlReader(Ui::MainWindow *ui, ViewChanger *changer)
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
            ClearWidgets_();
            ReadXmlData_();
            return true;
        }
    }

    return false;
}

// methods (private)
void XmlReader::ClearWidgets_()
{
    draft_view_->clear();
    plot_view_->clear();
    persons_view_->clear();
    worlds_view_->clear();
    research_view_->clear();
    notes_view_->clear();
    rubi_view_->clear();
    trash_view_->clear();
}

void XmlReader::ReadXmlData_()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "sms-data");

    while (!xml_.atEnd()) {
        xml_.readNextStartElement();

        if (xml_.name() == "category-bookinfo") {
            ReadBookInfo_();
        } else if (xml_.name() == "category-draft") {
            ReadDraft_();
        } else if (xml_.name() == "category-plot") {
            ReadPlot_();
        } else if (xml_.name() == "category-persons") {
            ReadPersons_();
        } else if (xml_.name() == "category-worlds") {
            ReadWorlds_();
        } else if (xml_.name() == "category-research") {
            ReadResearch_();
        } else if (xml_.name() == "category-notes") {
            ReadNotes_();
        } else if (xml_.name() == "category-rubis") {
            ReadRubis_();
        } else if (xml_.name() == "category-trashbox") {
            ReadTrash_();
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadBookInfo_()
{
    bookinfo_editor_->Clear();

    TreeItem *data = bookinfo_editor_->GetCurrentItem();

    bool isMatch = false;
    while (xml_.readNextStartElement()) {
        isMatch = false;
        for (int i = 0; i < ItemKeys::kBookInfoStrList.count(); ++i) {
            if (xml_.name() == ItemKeys::kBookInfoStrList.at(i).toLower()) {
                data->SetData(i, xml_.readElementText());
                isMatch = true;
                break;
            }
        }
        if (!isMatch)
            xml_.skipCurrentElement();
    }

    bookinfo_editor_->UpdateView();
}

void XmlReader::ReadDraftFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = draft_view_->CreateChild_(item);
    TreeItem *data = draft_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "synopsys") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else if (xml_.name() == "pov") {
            data->SetData(4, xml_.readElementText());
        } else if (xml_.name() == "stage") {
            data->SetData(5, xml_.readElementText());
        } else if (xml_.name() == "date") {
            data->SetData(6, xml_.readElementText());
        } else if (xml_.name() == "time") {
            data->SetData(7, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadDraftFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = draft_view_->CreateChild_(item);
    TreeItem *data = draft_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadDraftFolder_(child);
        } else if (xml_.name() == "file") {
            ReadDraftFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadDraft_()
{
    draft_view_->clear();

    QTreeWidgetItem *root = draft_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadDraftFolder_(root);
        } else if (xml_.name() == "file") {
            ReadDraftFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadNotesFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = notes_view_->CreateChild_(item);
    TreeItem *data = notes_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "synopsys") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadNotesFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = notes_view_->CreateChild_(item);
    TreeItem *data = notes_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadNotesFolder_(child);
        } else if (xml_.name() == "file") {
            ReadNotesFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadNotes_()
{
    QTreeWidgetItem *root = notes_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadNotesFolder_(root);
        } else if (xml_.name() == "file") {
            ReadNotesFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadPersonsFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = persons_view_->CreateChild_(item);
    TreeItem *data = persons_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "name") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "info") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else if (xml_.name() == "age") {
            data->SetData(4, xml_.readElementText());
        } else if (xml_.name() == "gender") {
            data->SetData(5, xml_.readElementText());
        } else if (xml_.name() == "job") {
            data->SetData(6, xml_.readElementText());
        } else if (xml_.name() == "appearance") {
            data->SetData(7, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadPersonsFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = persons_view_->CreateChild_(item);
    TreeItem *data = persons_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadPersonsFolder_(child);
        } else if (xml_.name() == "file") {
            ReadPersonsFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadPersons_()
{
    QTreeWidgetItem *root = persons_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadPersonsFolder_(root);
        } else if (xml_.name() == "file") {
            ReadPersonsFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}


void XmlReader::ReadPlotFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = plot_view_->CreateChild_(item);
    TreeItem *data = plot_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "synopsys") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadPlotFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = plot_view_->CreateChild_(item);
    TreeItem *data = plot_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadPlotFolder_(child);
        } else if (xml_.name() == "file") {
            ReadPlotFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadPlot_()
{
    QTreeWidgetItem *root = plot_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadPlotFolder_(root);
        } else if (xml_.name() == "file") {
            ReadPlotFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadResearchFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = research_view_->CreateChild_(item);
    TreeItem *data = research_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "synopsys") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadResearchFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = research_view_->CreateChild_(item);
    TreeItem *data = research_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadResearchFolder_(child);
        } else if (xml_.name() == "file") {
            ReadResearchFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadResearch_()
{
    QTreeWidgetItem *root = research_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadResearchFolder_(root);
        } else if (xml_.name() == "file") {
            ReadResearchFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadRubisFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = rubi_view_->CreateChild_(item);
    TreeItem *data = rubi_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "name") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "key") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "converted") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "always") {
            data->SetData(3, xml_.readElementText());
        } else if (xml_.name() == "exclusions") {
            data->SetData(4, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadRubisFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = rubi_view_->CreateChild_(item);
    TreeItem *data = rubi_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadRubisFolder_(child);
        } else if (xml_.name() == "file") {
            ReadRubisFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadRubis_()
{
    QTreeWidgetItem *root = rubi_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadRubisFolder_(root);
        } else if (xml_.name() == "file") {
            ReadRubisFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadTrashFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = trash_view_->CreateChild_(item);
    TreeItem *data = trash_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        for (int i = 0; i < data->ColumnCount(); ++i) {
            if (xml_.name() == QString("data-%1").arg(i)) {
                QString tmp = xml_.readElementText();
                data->SetData(i, tmp);
                if (i == 0)
                    child->setText(0, tmp);
            }
        }
    }
}

void XmlReader::ReadTrashFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = trash_view_->CreateChild_(item);
    TreeItem *data = trash_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadTrashFolder_(child);
        } else if (xml_.name() == "file") {
            ReadTrashFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadTrash_()
{
    QTreeWidgetItem *root = trash_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadTrashFolder_(root);
        } else if (xml_.name() == "file") {
            ReadTrashFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadWorldsFile_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "file");

    QTreeWidgetItem *child = worlds_view_->CreateChild_(item);
    TreeItem *data = worlds_view_->CreateFileItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "name") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "info") {
            data->SetData(1, xml_.readElementText());
        } else if (xml_.name() == "text") {
            data->SetData(2, xml_.readElementText());
        } else if (xml_.name() == "note") {
            data->SetData(3, xml_.readElementText());
        } else if (xml_.name() == "category") {
            data->SetData(4, xml_.readElementText());
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadWorldsFolder_(QTreeWidgetItem *item)
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "folder");

    QTreeWidgetItem *child = worlds_view_->CreateChild_(item);
    TreeItem *data = worlds_view_->CreateFolderItem_();
    child->setData(0, Qt::UserRole, QVariant::fromValue(data));

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            child->setText(0, title);
            data->SetData(0, title);
        } else if (xml_.name() == "folding") {
            child->setExpanded(QVariant(xml_.readElementText()).toBool());
        } else if (xml_.name() == "folder") {
            ReadWorldsFolder_(child);
        } else if (xml_.name() == "file") {
            ReadWorldsFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadWorlds_()
{
    QTreeWidgetItem *root = worlds_view_->invisibleRootItem();

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "folder") {
            ReadWorldsFolder_(root);
        } else if (xml_.name() == "file") {
            ReadWorldsFile_(root);
        } else {
            xml_.skipCurrentElement();
        }
    }
}

