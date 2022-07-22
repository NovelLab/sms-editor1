#ifndef FORMATTER_H
#define FORMATTER_H

#include <QStringList>

enum class BuildType;

class Formatter
{
public:
    explicit Formatter();

    QStringList FormatByType(BuildType type, const QStringList &data);

private:
    QStringList SimpleFormat_(const QStringList &data);
    QStringList NovelFormat_(const QStringList &data);
};

#endif // FORMATTER_H
