#ifndef ITEMKEYS_H
#define ITEMKEYS_H

#include <QStringList>

namespace ItemKeys {

// TODO: 全部をkeyで取得、設定できるようにする

enum class CommonKey {
    Title = 0,
    Info,
    Text,
    Note,
};

enum class BookInfo {
    Title = 0,
    Subtitle,
    Series,
    Volume,
    Genre,
    License,
    AuthorName,
    Email,
    OneLine,
    ThreeLines,
    Abstract,
};

constexpr int kBookInfoTypeCount = static_cast<int>(BookInfo::Abstract) + 1;
const QStringList kBookInfoStrList = {
  "Title",
    "Subtitle",
    "Series",
    "Volume",
    "Genre",
    "License",
    "AuthorName",
    "Email",
    "OneLine",
    "ThreeLines",
    "Abstract",
};

enum class Draft {
    Title = 0,
    Synopsys,
    Text,
    Note,
    POV,
    Stage,
    Date,
    Time,
};

enum class Plot {
    Title = 0,
    Synopsys,
    Text,
    Note,
};

enum class Person {
    Name = 0,
    Info,
    Text,
    Note,
    Fullname,
    Age,
    Gender,
    Job,
    Appearance,
};

enum class World {
    Name = 0,
    Info,
    Text,
    Note,
    Division,
};

enum class Research {
    Title = 0,
    Synopsys,
    Text,
    Note,
};

enum class Note {
    Title = 0,
    Info,
    Text,
};

enum class Rubi {
    Name = 0,
    Keyword,
    Converted,
    Always,
    Exclusions,
};

}
#endif // ITEMKEYS_H
