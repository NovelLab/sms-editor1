#ifndef FORMATTER_H
#define FORMATTER_H

#include <QStringList>

enum class BuildType;
enum class BuildStyle;

class Formatter
{
public:
    explicit Formatter();

    QStringList FormatByType(BuildType type, BuildStyle style, const QStringList &data);

private:
    QStringList SimpleFormat_(const QStringList &data);
    QStringList NovelFormat_(BuildStyle style, const QStringList &data);

    bool IsHeadline_(const QString &text) const;
    bool IsDialogueStart_(const QString &text) const;
    bool IsDialogueEnd_(const QString &text) const;
    bool IsBreakline_(const QString &text, bool is_mark = false) const;
    bool IsInstruction_(const QString &text) const;

    QString DescriptionEndValid(const QString &text);
};

#endif // FORMATTER_H
