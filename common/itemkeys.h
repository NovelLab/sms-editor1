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

enum class Count {
    Full = 0,
    WhiteSpaces,
};

constexpr int kCountSize = static_cast<int>(Count::WhiteSpaces) + 1;

}

namespace ItemDefVals {

const QStringList kBookInfo = {
    "タイトル",
    "サブタイトル",
    "シリーズ",
    "巻",
    "ジャンル",
    "ライセンス",
    "著者名",
    "Eメール",
    "１行物語",
    "３行解説",
    "梗概",
};

const QStringList kDraft = {
    "new draft",
    "synopsys",
    "new text",
    "new note",
    "POV",
    "stage",
    "date",
    "time",
};

const QStringList kPlot = {
    "new plot",
    "synopsys",
    "new text",
    "new note",
};

const QStringList kPerson = {
    "new person",
    "person info",
    "new text",
    "new note",
    "fullname",
    "99",
    "gender",
    "job",
    "appearance",
};

const QStringList kWorld = {
    "new world",
    "world info",
    "new text",
    "new note",
    "world division",
};

const QStringList kResearch = {
    "new research",
    "synopsys",
    "new text",
};

const QStringList kNote = {
    "new note",
    "info",
    "new text",
};

const QStringList kRubi = {
    "new rubi",
    "keyword",
    "converted",
    "false",
    "",
};

}

#endif // ITEMKEYS_H
