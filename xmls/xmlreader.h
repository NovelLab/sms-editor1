#ifndef XMLREADER_H
#define XMLREADER_H

#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DraftTree;
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
    void ReadCategory_();

    void ReadDraft_();
    void ReadDraftFolder_(QTreeWidgetItem *item);
    void ReadDraftFile_(QTreeWidgetItem *item);

    QXmlStreamReader xml_;
    DraftTree *draft_view_;
};



#endif // XMLREADER_H
