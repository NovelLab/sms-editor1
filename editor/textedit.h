#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class TreeItem;

class TextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);

    void LineNumberAreaPaintEvent(QPaintEvent *event);
    int LineNumberAreaWidth();

    void SaveCurrentItem();
    void UpdateView(const QTreeWidgetItem *item, bool isReadonly = false);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void UpdateLineNumberAreaWidth(int newBlockCount);
    void HighlightCurrentLine();
    void UpdateLineNumberArea(const QRect &rect, int dy);

private:
    void SaveToCurrentItem_();

    QWidget *linenumber_area_;
    TreeItem *current_item_ = nullptr;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEdit *editor) : QWidget(editor), editor_(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(editor_->LineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        editor_->LineNumberAreaPaintEvent(event);
    }

private:
    TextEdit *editor_;
};
#endif // TEXTEDIT_H
