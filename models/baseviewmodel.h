#ifndef BASEVIEWMODEL_H
#define BASEVIEWMODEL_H

#include <QAbstractItemModel>

class BaseViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit BaseViewModel(QObject *parent = nullptr);
};

#endif // BASEVIEWMODEL_H
