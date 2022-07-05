#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H

#include <QObject>

class ConfigModel;

class GlobalSetting: public QObject
{
    Q_OBJECT
public:
    explicit GlobalSetting();
    ~GlobalSetting();

    ConfigModel* GetModel();

public slots:
    void UpdateUi();

private:
    ConfigModel *model_;
};

#endif // GLOBALSETTING_H
