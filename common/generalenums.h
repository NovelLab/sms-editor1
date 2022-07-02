#ifndef GENERALENUMS_H
#define GENERALENUMS_H

namespace GeneralType {

enum class Category {
    BookInfo = 0,
    Draft,
    Plot,
    Persons,
    Worlds,
    Research,
    Notes,
    Rubi,
    Trash,
    None = 99,
};

enum class ItemType {
    Folder = 0,
    File,
    None = 99,
};

}

#endif // GENERALENUMS_H
