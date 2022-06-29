#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DraftTree;
class PersonTree;
class PlotTree;
class QTreeWidgetItem;

enum class Category;

class XmlReader
{
public:
    explicit XmlReader(Ui::MainWindow *ui);

    bool Read(QIODevice *device);
    QString ErrorString() const;

private:
    void ReadXmlData_();

    void ReadDraft_();
    void ReadDraftFolder_(QTreeWidgetItem *item);
    void ReadDraftFile_(QTreeWidgetItem *item);

    void ReadPlot_();
    void ReadPlotFolder_(QTreeWidgetItem *item);
    void ReadPlotFile_(QTreeWidgetItem *item);

    void ReadPersons_();
    void ReadPersonsFolder_(QTreeWidgetItem *item);
    void ReadPersonsFile_(QTreeWidgetItem *item);

    void ClearWidgets_();

    QXmlStreamReader xml_;
    DraftTree *draft_view_;
    PlotTree *plot_view_;
    PersonTree *persons_view_;
};



#endif // XMLREADER_H
