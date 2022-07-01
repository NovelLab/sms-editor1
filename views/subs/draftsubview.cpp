#include "draftsubview.h"

#include "ui_mainwindow.h"

#include "enums/generaltypes.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

DraftSubView::DraftSubView(Ui::MainWindow *ui)
    : file_title_{ui->lblDraftTitle},
      pov_{ui->linePOVDraft},
      stage_{ui->lineStageDraft},
      date_{ui->lineDateDraft},
      time_{ui->lineTimeDraft},
      synop_{ui->txtEditSynopDraft},
      note_{ui->txtEditNoteDraft}
{

}

// methods
void DraftSubView::UpdateView(const QTreeWidgetItem *item)
{
    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;

    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data && util.IsFile(item)) {
        file_title_->setText(data->DataOf(0).toString());
        pov_->setText(data->DataOf(4).toString());
        stage_->setText(data->DataOf(5).toString());
        date_->setText(data->DataOf(6).toString());
        time_->setText(data->DataOf(7).toString());
        synop_->setPlainText(data->DataOf(1).toString());
        note_->setPlainText(data->DataOf(3).toString());
    }
}
