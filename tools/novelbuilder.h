#ifndef NOVELBUILDER_H
#define NOVELBUILDER_H

#include <QString>

class QTreeWidgetItem;
class ItemData;

class NovelBuilder
{
public:
    explicit NovelBuilder();

    bool Build(const QTreeWidgetItem *item, const QString &filename = "output.txt");

private:
    QString NovelDataFromFolder(const QTreeWidgetItem *item);
    QString NovelDataFromFile(ItemData *data);
};

#endif // NOVELBUILDER_H
