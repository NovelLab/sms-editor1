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

    for (int i = 0; i < data.count(); ++i) {
        QString text = data.at(i);
        if (text.startsWith("「")
                || text.startsWith("『")
                || text.startsWith("# ")) {
            formatted << text + "\n";
        } else if (text == "") {
            formatted << "\n";
        } else {
            if (text.endsWith("。")
                    || text.endsWith("、")
                    || text.endsWith("」")
                    || text.endsWith("』")
                    || text.endsWith("？")
                    || text.endsWith("！")) {
                formatted << "　" + text + "\n";
            } else {
                formatted << "　" + text + "。\n";
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
