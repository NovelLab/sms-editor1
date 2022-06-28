#include "xmlreader.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "views/drafttree.h"
#include "utils/itemutility.h"

#include <QDebug>

XmlReader::XmlReader(Ui::MainWindow *ui)
{
    draft_view_ = ui->draftTreeView;
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
}

void XmlReader::ReadXmlData_()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "sms-data");

    while (!xml_.atEnd()) {
        xml_.readNextStartElement();

        if (xml_.name() == "category") {
            ReadCategory_();
        } else {
            xml_.skipCurrentElement();
        }
    }
}

void XmlReader::ReadCategory_()
{
    Q_ASSERT(xml_.isStartElement() && xml_.name() == "category");

    while (xml_.readNextStartElement()) {
        if (xml_.name() == "title") {
            QString title = xml_.readElementText();
            if (title == "bookinfo") {
                qDebug() << "(unimp) read xml: project info";
            } else if (title == "draft") {
                ReadDraft_();
            } else if (title == "plot") {
                qDebug() << "(unimp) read xml: plot";
            } else if (title == "persons") {
                qDebug() << "(unimp) read xml: person";
            } else if (title == "worlds") {
                qDebug() << "(unimp) read xml: world";
            } else if (title == "research") {
                qDebug() << "(unimp) read xml: research";
            } else if (title == "notes") {
                qDebug() << "(unimp) read xml: note";
            } else if (title == "rubi") {
                qDebug() << "(unimp) read xml: rubi";
            } else {
                // TODO: warning message.
            }
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
        } else if (xml_.name() == "folder") {
            ReadDraftFolder_(child);
        } else if (xml_.name() == "file") {
            ReadDraftFile_(child);
        } else {
            xml_.skipCurrentElement();
        }
    }
}
