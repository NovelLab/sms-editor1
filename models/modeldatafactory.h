#ifndef MODELDATAFACTORY_H
#define MODELDATAFACTORY_H

#include <QVariant>

namespace GeneralType {
enum class Category;
}

class TreeItem;

class ModelDataFactory
{
public:
    ModelDataFactory(GeneralType::Category cat);

    int ColumnCount() const;
    QVariant HeaderData(int section) const;

    QStringList CreateHeaderStrings() const;

    QVariant FileDataFromItem(const TreeItem *data, int column) const;
    QVariant FolderDataFromItem(const TreeItem *data, int column) const;
    bool SetFileData(TreeItem *data, int column, const QVariant &value);
    bool SetFolderData(TreeItem *data, int column, const QVariant &value);

private:
    QVariant FileDataOfDraft_(const TreeItem *data, int column) const;
    QVariant FileDataOfPlot_(const TreeItem *data, int column) const;
    QVariant FileDataOfPerson_(const TreeItem *data, int column) const;
    QVariant FileDataOfWorld_(const TreeItem *data, int column) const;
    QVariant FileDataOfResearch_(const TreeItem *data, int column) const;
    QVariant FileDataOfNote_(const TreeItem *data, int column) const;
    QVariant FileDataOfRubi_(const TreeItem *data, int column) const;
    QVariant FileDataOfTrash_(const TreeItem *data, int column) const;
    bool SetFileDataOfDraft_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfPlot_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfPerson_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfWorld_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfResearch_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfNote_(TreeItem *data, int column, const QVariant &value);
    bool SetFileDataOfRubi_(TreeItem *data, int column, const QVariant &value);
    bool IsValidColumn_(int column, GeneralType::Category cat) const;

    GeneralType::Category cat_;
};

#endif // MODELDATAFACTORY_H
