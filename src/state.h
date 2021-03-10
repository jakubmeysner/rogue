#pragma once

#include <vector>
#include <optional>
#include <sstream>
#include <iomanip>
#include <map>

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

class Position {
public:
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int x = 0;
    int y = 0;

    bool operator<(Position const &r) const {
        return this->x < r.x;
    }
};

enum class ItemType {
    SWORD, BOW, ARMOR, ARROWS
};

class Item {
public:
    ItemType type = ItemType::SWORD;

    int damage = 10;

    double sweep = 0.1;

    int range = 10;

    double protection = 0.3;
    double criticalProtection = 0.1;

    int durability = 20;

    int count = 5;

    std::string getShortInfo() {
        std::stringstream str;
        str << std::setprecision(2) << "(";

        switch (this->type) {
            case ItemType::SWORD:
                str << this->damage << ", " << this->sweep << ", " << this->durability;
                break;
            case ItemType::BOW:
                str << this->damage << ", " << this->range << ", " << this->durability;
                break;
            case ItemType::ARMOR:
                str << this->protection << ", " << this->criticalProtection << ", " << this->durability;
                break;
            case ItemType::ARROWS:
                str << this->count;
                break;
        }

        str << ")";
        return str.str();
    }
};

class Block {
public:
    BlockType type = BlockType::EMPTY;
    std::optional<Item> item;
};

typedef std::vector<std::vector<Block>> World;

enum class EntityType {
    ZOMBIE, ARCHER, BOOMER
};

class Entity {
public:
    EntityType type = EntityType::ZOMBIE;
    Position position = Position(0, 0);
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

    std::optional<Item> sword;
    std::optional<Item> bow;
    std::optional<Item> armor;

    int arrows = 0;
    int maxArrows = 5;

    int keys = 0;

    std::vector<Entity> entities;
};
