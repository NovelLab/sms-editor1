#include "counter.h"

#include "common/itemkeys.h"
#include "items/countitem.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>

Counter::Counter()
{

}

// methods
CountItem* Counter::TextCharCountFrom(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return nullptr;

    int full_counts = 0;
    int white_counts = 0;

    if (util.IsFolder(item)) {
        full_counts = CountFolder_(item, ItemKeys::Count::Full);
        white_counts = CountFolder_(item, ItemKeys::Count::WhiteSpaces);
    } else if (util.IsFile(item)) {
        full_counts = CountFile_(item, ItemKeys::Count::Full);
        white_counts = CountFile_(item, ItemKeys::Count::WhiteSpaces);
    }

    CountItem *res = new CountItem();
    res->SetData(ItemKeys::Count::Full, full_counts);
    res->SetData(ItemKeys::Count::WhiteSpaces, white_counts);
    return res;
}

// methods (private)
int Counter::CountFile_(const QTreeWidgetItem *item, ItemKeys::Count type)
{
    Q_ASSERT(item);
    ItemUtility util;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    int count = 0;
    QString base_text = data->DataOf(ItemKeys::CommonKey::Text).toString().trimmed();
    if (ItemKeys::Count::Full == type) {
        count = base_text.remove(QChar('\n')).length();
    } else if (ItemKeys::Count::WhiteSpaces == type) {
        count = base_text.simplified().remove(QChar(' ')).length();
    }
    return count;
}

int Counter::CountFolder_(const QTreeWidgetItem *item, ItemKeys::Count type)
{
    Q_ASSERT(item);
    ItemUtility util;
    int count = 0;
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (util.IsFolder(child)) {
            count += CountFolder_(child, type);
        } else if (util.IsFile(child)) {
            count += CountFile_(child, type);
        }
    }
    return count;
}
