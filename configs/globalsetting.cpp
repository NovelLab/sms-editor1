#include "globalsetting.h"

#include "common/configenums.h"
#include "configs/configmodel.h"

#include <QApplication>
#include <QFont>
#include <QPalette>

GlobalSetting::GlobalSetting()
    : QObject()
{
    model_ = new ConfigModel();
}

GlobalSetting::~GlobalSetting()
{
    delete model_;
}

// slots
void GlobalSetting::UpdateUi()
{
    QFont font;
    font.setFamily(model_->DataOf(Config::UI::FontFamily).toString());
    font.setPointSize(model_->DataOf(Config::UI::FontSize).toInt());
    QString style = QString("QWidget {color: %1;}").arg(model_->DataOf(Config::UI::FontColor).toString());
    qApp->setFont(font);
    qApp->setStyleSheet(style);
}

// methods
ConfigModel* GlobalSetting::GetModel()
{
    return model_;
}
