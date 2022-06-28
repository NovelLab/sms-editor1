#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class MarkdownHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MarkdownHighlighter(QTextDocument *parent = nullptr);

    void SetBaseFontSize(int size);

protected:
    virtual void highlightBlock(const QString &text) override;

private:
    void InitRules_();

    struct HighlightRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> highlight_rules_;

    QTextCharFormat keyword_format_;
    QTextCharFormat single_comment_format_;
    QTextCharFormat headline_level1_;
    QTextCharFormat headline_level2_;
    QTextCharFormat headline_level3_;
    QTextCharFormat headline_level4_;
    QTextCharFormat headline_level5_;
    QTextCharFormat headline_level6_;

    int base_font_size_;
};

#endif // MARKDOWNHIGHLIGHTER_H
