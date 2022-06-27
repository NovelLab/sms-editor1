#ifndef VIEWCHANGER_H
#define VIEWCHANGER_H

enum class Category;

class ViewChanger
{
public:
    explicit ViewChanger();
    ~ViewChanger();

    void Change(Category category);

private:
    void ChangeBookInfo_();
    void ChangeDraft_();
    void ChangePlot_();
    void ChangePersons_();
    void ChangeWorlds_();
    void ChangeResearch_();
    void ChangeNotes_();
    void ChangeRubi_();
    void ChangeTrash_();
};

#endif // VIEWCHANGER_H
