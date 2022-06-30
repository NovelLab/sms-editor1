#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class DraftTree;
class PlotTree;
class PersonTree;
class ResearchTree;
class TreeItem;
class WorldTree;

class XmlWriter
{
public:
    explicit XmlWriter(const Ui::MainWindow *ui);

    bool WriteFile(QIODevice *device);

private:
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

    QXmlStreamWriter xml_;
    const DraftTree *draft_view_;
    const PlotTree *plot_view_;
    const PersonTree *persons_view_;
    const WorldTree *worlds_view_;
    const ResearchTree *research_view_;
};


#endif // XMLWRITER_H
