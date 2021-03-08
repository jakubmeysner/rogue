#pragma once

enum class Screen {
    MAIN_MENU, SETTINGS, SETTINGS_DIFFICULTY_LEVEL
};

enum class MainMenuOption {
    PLAY, SETTINGS, EXIT
};

enum class SettingsOption {
    CHANGE_DIFFICULTY_LEVEL, RESET_PROGRESS, BACK
};

enum SettingsDifficultyLevelOption {
    EASY, NORMAL, HARD, BACK
};

enum class DifficultyLevel {
    EASY, NORMAL, HARD
};

class State {
public:
    bool exit = false;

    Screen screen = Screen::MAIN_MENU;
    bool changedScreen = false;

    MainMenuOption mainMenuOption = MainMenuOption::PLAY;
    SettingsOption settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
    SettingsDifficultyLevelOption settingsDifficultyLevelOption = SettingsDifficultyLevelOption::EASY;

    bool initialLoadPerformed = false;
    bool pendingSave = false;

    bool playedOnce = false;
    DifficultyLevel difficultyLevel = DifficultyLevel::NORMAL;
};
