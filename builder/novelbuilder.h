#ifndef NOVELBUILDER_H
#define NOVELBUILDER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class OutlineView;
class RubiMaker;
enum class BuildType;

class NovelBuilder
{
public:
    explicit NovelBuilder(const Ui::MainWindow *ui);
    ~NovelBuilder();

    bool Build(QIODevice *devic, BuildType type, bool with_rubi = false);

private:
    QStringList OutputStrsFromFile(const QTreeWidgetItem *item);
    QStringList OutputStrsFromFolder(const QTreeWidgetItem *item);

    const OutlineView *draft_view_;
    RubiMaker *rubimaker_;
};

#endif // NOVELBUILDER_H
