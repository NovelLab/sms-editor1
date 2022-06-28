#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class DraftTree;
class TreeItem;

class XmlWriter
{
public:
    explicit XmlWriter(const Ui::MainWindow *ui);
    bool WriteFile(QIODevice *device);

private:
    void WriteDraft_();
    void WriteDraftFolder_(const QTreeWidgetItem *item);
    void WriteDraftFile_(const QTreeWidgetItem *item);

    QXmlStreamWriter xml_;
    const DraftTree *draft_view_;
};


#endif // XMLWRITER_H
