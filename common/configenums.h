#ifndef CONFIGENUMS_H
#define CONFIGENUMS_H

namespace Config {

enum class UI {
    FontFamily = 0,
    FontSize,
    FontColor,
};

constexpr int kUiCount = static_cast<int>(UI::FontColor) + 1;

constexpr int kConfigDataCount = kUiCount;

}

#endif // CONFIGENUMS_H
