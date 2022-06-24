#ifndef DATAENUMS_H
#define DATAENUMS_H

enum class DataType {
    Category,
    Folder,
    File,
    None,
};

enum class FileType {
    General,
    Draft,
    Plot,
    Person,
    Stage,
    Item,
    Word,
    Research,
    Note,
    Trash,
    None,
    // TODO: Rubi
};

enum class KeyGeneral {
    BookTitle,
    BookSubtitle,
    BookSeries,
    BookVolume,
    BookGenre,
    BookLicense,
    AuthorName,
    AuthorEmail,
};

enum class KeyCategory {
    Title,
};

enum class KeyFolder {
    Title,
};

enum class KeyDraft {
    Title,
    Synopsys,
    Text,
    Note,
};

enum class KeyPlot {
    Title,
    Synopsys,
    Text,
    Note,
};

enum class KeyPerson {
    Name,
    Info,
    Text,
    Note,
    Age,
    Gender,
    Job,
};

enum class KeyStage {
    Name,
    Info,
    Text,
    Note,
};

enum class KeyItem {
    Name,
    Info,
    Text,
    Note,
    Category,
};

enum class KeyWord {
    Name,
    Info,
    Text,
    Note,
};

enum class KeyResearch {
    Title,
    Synopsys,
    Text,
    Note,
};

enum class KeyNote {
    Title,
    Synopsys,
    Text,
    Note,
};


#endif // DATAENUMS_H
