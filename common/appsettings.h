#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

namespace AppSettings {
const QString kProjectPath = "PROJECT_PATH";
const QString kProjectFilename = "PROJECT_FILENAME";
const QString kBuildPath = "BUILD_PATH";
const QString kBuildFilename = "BUILD_FILENAME";
const QString kBuildExtension = "BUILD_EXT";
}

namespace AppConfigs {
// General
// Project
const QString kProjectPath = "PROJECT_PATH";
// UI
const QString kUiFontSize = "UI_FONT_SIZE";
const QString kUiFontFamily = "UI_FONT_FAMILY";
const QString kUiFontColor = "UI_FONT_COLOR";
const QString kUiBackground = "UI_BACKGROUND";
// View
const QString kViewBackgroundImage = "CorkBoard.jpg";
// Editor
const QString kEditorFontSize = "EDITOR_FONT_SIZE";
const QString kEditorFontFamily = "EDITOR_FONT_FAMILY";
const QString kEditorFontColor = "EDITOR_FONT_COLOR";
const QString kEditorBackground = "EDITOR_BACKGROUND";
// Compile
const QString kBuildDir = "COMP_BUILD_DIR";
const QString kBuildFileName = "COMP_BUILD_FILE_NAME";
const QString kBuildFileType = "COMP_BUILD_FILE_TYPE";
}

namespace DefaultSettings {
// General
// TODO: linux or win or mac
const QString kProjectPath = "/";
const QString kBuildPath = "build";
const QString kBuildFilename = "output";
const QString kBuildExtension = "txt";
// Font
const int kFontSize = 12;
const QString kFontColor = "#FFFFFF";
}

#endif // APPSETTINGS_H
