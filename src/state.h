#pragma once

enum class Screen {
    MAIN_MENU, SETTINGS
};

enum class MainMenuOption {
    PLAY, SETTINGS, EXIT
};

enum class SettingsOption {
    RESET_PROGRESS, BACK
};

class State {
public:
    bool exit = false;

    Screen screen = Screen::MAIN_MENU;
    bool changedScreen = false;

    MainMenuOption mainMenuOption = MainMenuOption::PLAY;
    SettingsOption settingsOption = SettingsOption::RESET_PROGRESS;
};
