#ifndef BOOKINFOTYPES_H
#define BOOKINFOTYPES_H

enum class BookInfoType {
    BookTitle = 0,
    BookSubtitle,
    BookSeries,
    BookVolume,
    BookGenre,
    BookLicense,
    AuthorName,
    AuthorEmail,
    Outline1Line,
    Outline3Lines,
    OutlineAbstract,
};

constexpr int kBookInfoTypeCount = static_cast<int>(BookInfoType::OutlineAbstract) + 1;

#endif // BOOKINFOTYPES_H
