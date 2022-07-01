#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

namespace AppSettings {
const QString kProjectPath = "PROJECT_PATH";
const QString kBuildPath = "BUILD_PATH";
const QString kBuildFilename = "BUILD_FILENAME";
}

namespace DefaultSettings {
const int kFontSize = 12;
const QString kBuildPath = "build";
const QString kBuildFilename = "output.md";
}

#endif // APPSETTINGS_H
