#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class OutlineView;
class BookInfoEditor;
class TreeItem;
class ViewChanger;

class XmlWriter
{
public:
    explicit XmlWriter(const Ui::MainWindow *ui, const ViewChanger *changer);

    bool WriteFile(QIODevice *device);

private:
    void WriteBookInfo_();
    void WriteDraft_();
    void WriteDraftFolder_(const QTreeWidgetItem *item);
    void WriteDraftFile_(const QTreeWidgetItem *item);
    void WritePlot_();
    void WritePlotFolder_(const QTreeWidgetItem *item);
    void WritePlotFile_(const QTreeWidgetItem *item);
    void WritePersons_();
    void WritePersonsFolder_(const QTreeWidgetItem *item);
    void WritePersonsFile_(const QTreeWidgetItem *item);
    void WriteWorlds_();
    void WriteWorldsFolder_(const QTreeWidgetItem *item);
    void WriteWorldsFile_(const QTreeWidgetItem *item);
    void WriteResearch_();
    void WriteResearchFolder_(const QTreeWidgetItem *item);
    void WriteResearchFile_(const QTreeWidgetItem *item);
    void WriteNotes_();
    void WriteNotesFolder_(const QTreeWidgetItem *item);
    void WriteNotesFile_(const QTreeWidgetItem *item);
    void WriteRubis_();
    void WriteRubisFolder_(const QTreeWidgetItem *item);
    void WriteRubisFile_(const QTreeWidgetItem *item);
    void WriteTrash_();
    void WriteTrashFolder_(const QTreeWidgetItem *item);
    void WriteTrashFile_(const QTreeWidgetItem *item);

    QXmlStreamWriter xml_;
    const BookInfoEditor *bookinfo_editor_;
    const OutlineView *draft_view_;
    const OutlineView *plot_view_;
    const OutlineView *persons_view_;
    const OutlineView *worlds_view_;
    const OutlineView *research_view_;
    const OutlineView *notes_view_;
    const OutlineView *rubi_view_;
    const OutlineView *trash_view_;
};


#endif // XMLWRITER_H
