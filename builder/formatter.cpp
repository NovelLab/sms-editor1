#include "formatter.h"

#include "common/buildenums.h"

#include <QDebug>

Formatter::Formatter()
{

}

// methods
QStringList Formatter::FormatByType(BuildType type, const QStringList &data)
{
    switch (type) {
      case BuildType::Simple:
        return SimpleFormat_(data);
      case BuildType::Novel:
        return NovelFormat_(data);
      default:
        return SimpleFormat_(data);
    }
}

// methods (private)
QStringList Formatter::NovelFormat_(const QStringList &data)
{
    QStringList formatted;
    bool shown_headline = true;
    bool in_paragraph = false;
    bool in_dialogue = false;

    for (int i = 0; i < data.count(); ++i) {
        QString text = data.at(i);
        if (IsHeadline_(text)) {
            if (in_paragraph || in_dialogue) {
                in_paragraph = false;
                in_dialogue = false;
                formatted << "\n";
            }
            // headline
            // TODO: shown switch
            if (shown_headline) {
                formatted << text + "\n";
            }
        } else if (IsDialogueStart_(text)){
            // dialogue start
            if (in_paragraph || in_dialogue) {
                formatted << "\n";
                in_paragraph = false;
            }
            in_dialogue = true;
            if (IsDialogueEnd_(text)) {
                formatted << text;
            } else {
                formatted << DescriptionEndValid(text);
            }
        } else if (IsBreakline_(text)) {
            // TODO: last formatted text check and endmark replace.
            if (in_paragraph || in_dialogue) {
                formatted << "\n";
                in_paragraph = false;
                in_dialogue = false;
            } else {
                formatted << "\n";
            }
            if (IsBreakline_(text, true))
                formatted << "\n";
        } else if (IsInstruction_(text)) {
            // TODO: instruction command switch
            if (text.startsWith("!")) {
                formatted << text.replace("!", "") + "\n";
            }
        } else {
            // description
            if (in_dialogue) {
                // continue dialogues
                formatted << DescriptionEndValid(text);
            } else if (in_paragraph) {
                // continue paragraph
                formatted << DescriptionEndValid(text);
            } else {
                // TODO: institute line check
                in_paragraph = true;
                formatted << "　" + DescriptionEndValid(text);
            }
        }
    }
    return formatted;
}

QStringList Formatter::SimpleFormat_(const QStringList &data)
{
    QStringList formatted;

    for (int i = 0; i < data.count(); ++i) {
        formatted << data.at(i) + "\n";
    }
    return formatted;
}

bool Formatter::IsBreakline_(const QString &text, bool is_mark) const
{
    if (is_mark) {
        return (text == "!BR" || text == "!br");
    } else {
        return (text == "!BR"
            || text == "!br"
            || text.startsWith("---")
            || text.startsWith("***")
            || text == "");
    }
}

bool Formatter::IsDialogueEnd_(const QString &text) const
{
    return (text.endsWith("」")
            || text.endsWith("』")
            || text.endsWith("）"));
}

bool Formatter::IsDialogueStart_(const QString &text) const
{
    return (text.startsWith("「")
            || text.startsWith("『")
            || text.startsWith("（"));
}

bool Formatter::IsHeadline_(const QString &text) const
{
    return (text.startsWith("# ")
            || text.startsWith("## ")
            || text.startsWith("### "));
}

bool Formatter::IsInstruction_(const QString &text) const
{
    return (text.startsWith("!"));
}

QString Formatter::DescriptionEndValid(const QString &text)
{
    if (text.endsWith("。")
            || text.endsWith("、")
            || text.endsWith("」")
            || text.endsWith("』")
            || text.endsWith("？")
            || text.endsWith("！")
            || text.endsWith("（了）")) {
        return text;
    } else {
        return text + "。";
    }
}
