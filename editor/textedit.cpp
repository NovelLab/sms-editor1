#include "textedit.h"

#include "common/itemkeys.h"
#include "items/treeitem.h"
#include "utils/itemutility.h"

#include <QTreeWidgetItem>
#include <QPainter>
#include <QTextBlock>

TextEdit::TextEdit(QWidget *parent)
    : QPlainTextEdit{parent}
{
    linenumber_area_ = new LineNumberArea(this);

    connect(this, &TextEdit::blockCountChanged, this, &TextEdit::UpdateLineNumberAreaWidth);
    connect(this, &TextEdit::updateRequest, this, &TextEdit::UpdateLineNumberArea);
    connect(this, &TextEdit::cursorPositionChanged, this, &TextEdit::HighlightCurrentLine);

    UpdateLineNumberAreaWidth(0);
    HighlightCurrentLine();
}

// overrides (protected)
void TextEdit::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    linenumber_area_->setGeometry(QRect(cr.left(), cr.top(), LineNumberAreaWidth(), cr.height()));
}

// methods
void TextEdit::LineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(linenumber_area_);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, linenumber_area_->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int TextEdit::LineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void TextEdit::SaveCurrentItem()
{
    if (current_item_ && this->document()->isModified())
        SaveToCurrentItem_();
}

void TextEdit::UpdateView(const QTreeWidgetItem *item, bool isReadOnly)
{
    SaveCurrentItem();

    ItemUtility util;
    if (!util.IsValidTreeWidgetItem(item))
        return;
    TreeItem *data = util.ItemFromTreeWidgetItem(item);
    if (data) {
        this->setPlainText(data->DataOf(ItemKeys::CommonKey::Text).toString());
        current_item_ = data;
        this->setReadOnly(isReadOnly);
    }
}

// slots (private)
void TextEdit::UpdateLineNumberAreaWidth(int newBlockCount)
{
    Q_UNUSED(newBlockCount);
    setViewportMargins(LineNumberAreaWidth(), 0, 0, 0);
}

void TextEdit::HighlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor("#66666666").lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void TextEdit::UpdateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        linenumber_area_->scroll(0, dy);
    else
        linenumber_area_->update(0, rect.y(), linenumber_area_->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        UpdateLineNumberAreaWidth(0);
}

// methods (private)
void TextEdit::SaveToCurrentItem_()
{
    if (!current_item_)
        return;

    current_item_->SetData(ItemKeys::CommonKey::Text, this->toPlainText());
}
