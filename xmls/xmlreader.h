#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class OutlineView;
class BookInfoEditor;
class ViewChanger;

class XmlReader
{
public:
    explicit XmlReader(Ui::MainWindow *ui, ViewChanger *changer);

    bool Read(QIODevice *device);
    QString ErrorString() const;

private:
    void ReadXmlData_();

    void ReadBookInfo_();

    void ReadDraft_();
    void ReadDraftFolder_(QTreeWidgetItem *item);
    void ReadDraftFile_(QTreeWidgetItem *item);

    void ReadPlot_();
    void ReadPlotFolder_(QTreeWidgetItem *item);
    void ReadPlotFile_(QTreeWidgetItem *item);

    void ReadPersons_();
    void ReadPersonsFolder_(QTreeWidgetItem *item);
    void ReadPersonsFile_(QTreeWidgetItem *item);

    void ReadWorlds_();
    void ReadWorldsFolder_(QTreeWidgetItem *item);
    void ReadWorldsFile_(QTreeWidgetItem *item);

    void ReadResearch_();
    void ReadResearchFolder_(QTreeWidgetItem *item);
    void ReadResearchFile_(QTreeWidgetItem *item);

    void ReadNotes_();
    void ReadNotesFolder_(QTreeWidgetItem *item);
    void ReadNotesFile_(QTreeWidgetItem *item);

    void ReadRubis_();
    void ReadRubisFolder_(QTreeWidgetItem *item);
    void ReadRubisFile_(QTreeWidgetItem *item);

    void ReadTrash_();
    void ReadTrashFolder_(QTreeWidgetItem *item);
    void ReadTrashFile_(QTreeWidgetItem *item);

    void ClearWidgets_();

    QXmlStreamReader xml_;
    BookInfoEditor *bookinfo_editor_;
    OutlineView *draft_view_;
    OutlineView *plot_view_;
    OutlineView *persons_view_;
    OutlineView *worlds_view_;
    OutlineView *research_view_;
    OutlineView *notes_view_;
    OutlineView *rubi_view_;
    OutlineView *trash_view_;
};

#endif // XMLREADER_H
