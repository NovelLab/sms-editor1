#ifndef GENERALTYPES_H
#define GENERALTYPES_H

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
};

#endif // GENERALTYPES_H
