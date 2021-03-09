#pragma once

enum class Screen {
    MAIN_MENU, SETTINGS, SETTINGS_DIFFICULTY_LEVEL, PLAY_DIFFICULTY_LEVEL, PLAY_LEVEL
};

enum class MainMenuOption {
    DEFAULT, PLAY, SETTINGS, EXIT
};

enum class SettingsOption {
    CHANGE_DIFFICULTY_LEVEL, RESET_PROGRESS, BACK
};

enum DifficultyLevelOption {
    EASY, NORMAL, HARD, BACK
};

enum class DifficultyLevel {
    EASY, NORMAL, HARD
};

enum class Level {
    OVERWORLD, MINES, HELL
};

enum class LevelOption {
    OVERWORLD, MINES, HELL, BACK
};

class State {
public:
    bool exit = false;

    Screen screen = Screen::MAIN_MENU;
    bool requiresRefresh = false;

    MainMenuOption mainMenuOption = MainMenuOption::DEFAULT;
    SettingsOption settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
    DifficultyLevelOption settingsDifficultyLevelOption = DifficultyLevelOption::EASY;
    DifficultyLevelOption playDifficultyLevelOption = DifficultyLevelOption::NORMAL;
    LevelOption playLevelOption = LevelOption::OVERWORLD;

    bool initialLoadPerformed = false;
    bool pendingSave = false;

    bool recentlyResetProgress = false;

    bool playedOnce = false;
    DifficultyLevel difficultyLevel = DifficultyLevel::NORMAL;
    Level unlockedLevel = Level::OVERWORLD;

    Level level = Level::OVERWORLD;
};
