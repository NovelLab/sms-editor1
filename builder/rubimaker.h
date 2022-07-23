#ifndef RUBIMAKER_H
#define RUBIMAKER_H

#include <QStringList>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTreeWidgetItem;
class OutlineView;
class TreeItem;

class RubiMaker
{
public:
    explicit RubiMaker(const Ui::MainWindow *ui);

    QStringList AddRubi(const QStringList &data);

private:
    void InitRubiDB_(const OutlineView *view);
    void InitRubiDBInFolder_(const QTreeWidgetItem *item);

    QVector<TreeItem*> items_;
};

#endif // RUBIMAKER_H
