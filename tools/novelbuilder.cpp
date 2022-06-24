#include "novelbuilder.h"

#include "items/dataenums.h"
#include "items/itemdata.h"

#include "tools/itemdatareader.h"

#include <QTreeWidgetItem>
#include <QFile>

#include <QDebug>

NovelBuilder::NovelBuilder()
{

}

// methods
bool NovelBuilder::Build(const QTreeWidgetItem *item, const QString &filename)
{
    if (!item)
        return false;

    QString outputs;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        ItemData *data = child->data(0, Qt::UserRole).value<ItemData*>();
        if (data->TypeOf() == DataType::Folder) {
            outputs += NovelDataFromFolder(child);
            outputs += "\n";
        } else if (data->TypeOf() == DataType::File) {
            outputs += NovelDataFromFile(data);
            outputs += "\n";
        }
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return false;
    }
    QTextStream out(&file);
    out << outputs;
    file.close();

    return true;
}

// private methods
QString NovelBuilder::NovelDataFromFile(ItemData *data)
{
    QString outputs;

    ItemDataReader reader;

    outputs += reader.ReadText(data).toString();

    return outputs;
}

QString NovelBuilder::NovelDataFromFolder(const QTreeWidgetItem *item)
{
    QString outputs;

    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        ItemData *data = child->data(0, Qt::UserRole).value<ItemData*>();
        if (data->TypeOf() == DataType::Folder) {
            outputs += NovelDataFromFolder(child);
            outputs += "\n";
        } else if (data->TypeOf() == DataType::File) {
            outputs += NovelDataFromFile(data);
            outputs += "\n";
        }
    }

    return outputs;
}
