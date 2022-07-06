#ifndef NOVELBUILDER_H
#define NOVELBUILDER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;

class OutlineView;

class NovelBuilder
{
public:
    explicit NovelBuilder(const Ui::MainWindow *ui);

    bool Build(QIODevice *devic);

private:
    QStringList OutputStrsFromFile(const QTreeWidgetItem *item);
    QStringList OutputStrsFromFolder(const QTreeWidgetItem *item);

    const OutlineView *draft_view_;
};

#endif // NOVELBUILDER_H
