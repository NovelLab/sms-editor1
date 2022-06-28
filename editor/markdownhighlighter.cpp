#include "markdownhighlighter.h"

#include <QDebug>

static const int kDefaultFntSoize = 10;

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter{parent},
      base_font_size_{kDefaultFntSoize}
{
    InitRules_();
}

// overrides (protected)
void MarkdownHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightRule &rule : qAsConst(highlight_rules_)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
}

// methods
void MarkdownHighlighter::SetBaseFontSize(int size)
{
    base_font_size_ = size;
}

// methods (private)
void MarkdownHighlighter::InitRules_()
{
    HighlightRule rule;

    // keyword
    keyword_format_.setForeground(Qt::red);
    keyword_format_.setFontWeight(QFont::Bold);

    const QString keyword_patterns[] = {
        QStringLiteral("TODO:"),
        QStringLiteral("NOTE:"),
    };

    for (const QString &pattern : keyword_patterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keyword_format_;
            highlight_rules_.append(rule);
    }

    // single line comment
    single_comment_format_.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = single_comment_format_;
    highlight_rules_.append(rule);

    // head line lv1
    headline_level1_.setFontWeight(QFont::Bold);
    headline_level1_.setForeground(Qt::yellow);
    headline_level1_.setFontPointSize(base_font_size_ * 1.5);
    rule.pattern = QRegularExpression(QStringLiteral("# [^\n]*"));
    rule.format = headline_level1_;
    highlight_rules_.append(rule);

    // head line lv2
    headline_level2_.setFontWeight(QFont::Bold);
    headline_level2_.setForeground(Qt::darkYellow);
    headline_level2_.setFontPointSize(base_font_size_ * 1.4);
    rule.pattern = QRegularExpression(QStringLiteral("## [^\n]*"));
    rule.format = headline_level2_;
    highlight_rules_.append(rule);

    // head line lv3
    headline_level3_.setFontWeight(QFont::Bold);
    headline_level3_.setFontPointSize(base_font_size_ * 1.3);
    rule.pattern = QRegularExpression(QStringLiteral("### [^\n]*"));
    rule.format = headline_level3_;
    highlight_rules_.append(rule);

    // head line lv4
    //headline_level4_.setFontWeight(QFont::Bold);
    headline_level4_.setFontPointSize(base_font_size_ * 1.2);
    rule.pattern = QRegularExpression(QStringLiteral("#### [^\n]*"));
    rule.format = headline_level4_;
    highlight_rules_.append(rule);

    // head line lv5
    //headline_level5_.setFontWeight(QFont::Bold);
    headline_level5_.setFontPointSize(base_font_size_ * 1.1);
    rule.pattern = QRegularExpression(QStringLiteral("##### [^\n]*"));
    rule.format = headline_level5_;
    highlight_rules_.append(rule);

    // head line lv6
    //headline_level6_.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("###### [^\n]*"));
    rule.format = headline_level6_;
    highlight_rules_.append(rule);
}
