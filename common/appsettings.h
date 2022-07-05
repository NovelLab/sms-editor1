#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

namespace AppSettings {
const QString kProjectPath = "PROJECT_PATH";
const QString kBuildPath = "BUILD_PATH";
const QString kBuildFilename = "BUILD_FILENAME";
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
// Editor
const QString kEditorFontSize = "EDITOR_FONT_SIZE";
const QString kEditorFontFamily = "EDITOR_FONT_FAMILY";
const QString kEditorFontColor = "EDITOR_FONT_COLOR";
const QString kEditorBackground = "EDITOR_BACKGROUND";
// Compile
const QString kBuildDir = "BUILD_DIR";
const QString kBuildFileName = "BUILD_FILE_NAME";
const QString kBuildFileType = "BUILD_FILE_TYPE";
}

namespace DefaultSettings {
const int kFontSize = 12;
const QString kBuildPath = "build";
const QString kBuildFilename = "output.md";
}

#endif // APPSETTINGS_H
