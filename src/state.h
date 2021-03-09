#pragma once

#include <vector>

enum class Screen {
    MAIN_MENU, SETTINGS, SETTINGS_DIFFICULTY_LEVEL, PLAY_DIFFICULTY_LEVEL, PLAY_LEVEL,
    LOADING, PAUSE_MENU, GAME
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

enum class PauseMenuOption {
    CONTINUE, EXIT
};

enum class BlockType {
    EMPTY,
    WALL, DOOR, EMPTY_INSIDE
};

class Block {
public:
    BlockType type = BlockType::EMPTY;
};

typedef std::vector<std::vector<Block>> World;

class Position {
public:
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int x = 0;
    int y = 0;
};

enum class ItemType {
    SWORD, BOW, ARMOR
};

class Item {
public:
    ItemType type = ItemType::SWORD;
};

class State {
public:
    bool exit = false;

    Screen screen = Screen::MAIN_MENU;

    MainMenuOption mainMenuOption = MainMenuOption::DEFAULT;
    SettingsOption settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
    DifficultyLevelOption settingsDifficultyLevelOption = DifficultyLevelOption::EASY;
    DifficultyLevelOption playDifficultyLevelOption = DifficultyLevelOption::NORMAL;
    LevelOption playLevelOption = LevelOption::OVERWORLD;
    PauseMenuOption pauseMenuOption = PauseMenuOption::CONTINUE;

    bool initialLoadPerformed = false;
    bool pendingClear = false;
    bool pendingSave = false;
    bool pendingGenerate = false;

    bool recentlyResetProgress = false;

    bool playedOnce = false;
    DifficultyLevel difficultyLevel = DifficultyLevel::NORMAL;
    Level unlockedLevel = Level::OVERWORLD;

    Level level = Level::OVERWORLD;
    World world = {{Block()}};
    Position playerPosition = Position(0, 0);

    int health = 10;
    int maxHealth = 10;
    int stamina = 10;
    int maxStamina = 10;
};
