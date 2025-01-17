#include "input.h"

bool wasKeyPressed(int key) {
    auto keyState = GetAsyncKeyState(key);
    return keyState != 0 && std::bitset<sizeof(short)>(keyState)[0] == 1;
}

void input(State *state) {
    while (true) {
        if (state->exit) break;

        switch (state->screen) {
            case Screen::MAIN_MENU:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->mainMenuOption) {
                        case MainMenuOption::PLAY:
                            if (!state->playedOnce) {
                                state->screen = Screen::PLAY_DIFFICULTY_LEVEL;
                                state->pendingClear = true;
                                state->mainMenuOption = MainMenuOption::PLAY;
                            } else {
                                if (state->unlockedLevel == Level::OVERWORLD) {
                                    state->playLevelOption = LevelOption::OVERWORLD;
                                } else if (state->unlockedLevel == Level::MINES) {
                                    state->playLevelOption = LevelOption::MINES;
                                } else if (state->unlockedLevel == Level::HELL) {
                                    state->playLevelOption = LevelOption::HELL;
                                }

                                state->screen = Screen::PLAY_LEVEL;
                                state->pendingClear = true;
                                state->mainMenuOption = MainMenuOption::PLAY;
                            }

                            break;
                        case MainMenuOption::SETTINGS:
                            state->screen = Screen::SETTINGS;
                            state->pendingClear = true;
                            state->mainMenuOption = MainMenuOption::PLAY;
                            break;
                        case MainMenuOption::EXIT:
                            state->exit = true;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->mainMenuOption) {
                        case MainMenuOption::DEFAULT:
                            state->mainMenuOption = MainMenuOption::PLAY;
                            break;
                        case MainMenuOption::PLAY:
                            state->mainMenuOption = MainMenuOption::EXIT;
                            break;
                        case MainMenuOption::SETTINGS:
                            state->mainMenuOption = MainMenuOption::PLAY;
                            break;
                        case MainMenuOption::EXIT:
                            state->mainMenuOption = MainMenuOption::SETTINGS;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->mainMenuOption) {
                        case MainMenuOption::DEFAULT:
                            state->mainMenuOption = MainMenuOption::DEFAULT;
                            break;
                        case MainMenuOption::PLAY:
                            state->mainMenuOption = MainMenuOption::SETTINGS;
                            break;
                        case MainMenuOption::SETTINGS:
                            state->mainMenuOption = MainMenuOption::EXIT;
                            break;
                        case MainMenuOption::EXIT:
                            state->mainMenuOption = MainMenuOption::PLAY;
                            break;
                    }
                }
                break;
            case Screen::SETTINGS:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->settingsOption) {
                        case SettingsOption::CHANGE_DIFFICULTY_LEVEL:
                            state->screen = Screen::SETTINGS_DIFFICULTY_LEVEL;
                            state->pendingClear = true;
                            state->settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
                            state->recentlyResetProgress = false;
                            break;
                        case SettingsOption::RESET_PROGRESS:
                            state->playedOnce = false;
                            state->difficultyLevel = DifficultyLevel::NORMAL;

                            state->pendingSave = true;
                            state->recentlyResetProgress = true;
                            break;
                        case SettingsOption::BACK:
                            state->screen = Screen::MAIN_MENU;
                            state->pendingClear = true;
                            state->settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
                            state->recentlyResetProgress = false;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->settingsOption) {
                        case SettingsOption::CHANGE_DIFFICULTY_LEVEL:
                            state->settingsOption = SettingsOption::BACK;
                            break;
                        case SettingsOption::RESET_PROGRESS:
                            state->settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
                            break;
                        case SettingsOption::BACK:
                            state->settingsOption = SettingsOption::RESET_PROGRESS;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->settingsOption) {
                        case SettingsOption::CHANGE_DIFFICULTY_LEVEL:
                            state->settingsOption = SettingsOption::RESET_PROGRESS;
                            break;
                        case SettingsOption::RESET_PROGRESS:
                            state->settingsOption = SettingsOption::BACK;
                            break;
                        case SettingsOption::BACK:
                            state->settingsOption = SettingsOption::CHANGE_DIFFICULTY_LEVEL;
                            break;
                    }
                }
                break;
            case Screen::SETTINGS_DIFFICULTY_LEVEL:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->settingsDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->difficultyLevel = DifficultyLevel::EASY;
                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->difficultyLevel = DifficultyLevel::NORMAL;
                            break;
                        case DifficultyLevelOption::HARD:
                            state->difficultyLevel = DifficultyLevel::HARD;
                            break;
                        case DifficultyLevelOption::BACK:
                            state->screen = Screen::SETTINGS;
                            state->pendingClear = true;
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::EASY;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->settingsDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::BACK;
                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::EASY;
                            break;
                        case DifficultyLevelOption::HARD:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::NORMAL;
                            break;
                        case DifficultyLevelOption::BACK:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::HARD;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->settingsDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::NORMAL;
                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::HARD;
                            break;
                        case DifficultyLevelOption::HARD:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::BACK;
                            break;
                        case DifficultyLevelOption::BACK:
                            state->settingsDifficultyLevelOption = DifficultyLevelOption::EASY;
                            break;
                    }
                }
                break;
            case Screen::PLAY_DIFFICULTY_LEVEL:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->playDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->difficultyLevel = DifficultyLevel::EASY;
                            state->screen = Screen::PLAY_LEVEL;
                            state->pendingClear = true;
                            state->playDifficultyLevelOption = NORMAL;

                            if (state->unlockedLevel == Level::OVERWORLD) {
                                state->playLevelOption = LevelOption::OVERWORLD;
                            } else if (state->unlockedLevel == Level::MINES) {
                                state->playLevelOption = LevelOption::MINES;
                            } else if (state->unlockedLevel == Level::HELL) {
                                state->playLevelOption = LevelOption::HELL;
                            }

                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->difficultyLevel = DifficultyLevel::NORMAL;
                            state->screen = Screen::PLAY_LEVEL;
                            state->pendingClear = true;
                            state->playDifficultyLevelOption = NORMAL;

                            if (state->unlockedLevel == Level::OVERWORLD) {
                                state->playLevelOption = LevelOption::OVERWORLD;
                            } else if (state->unlockedLevel == Level::MINES) {
                                state->playLevelOption = LevelOption::MINES;
                            } else if (state->unlockedLevel == Level::HELL) {
                                state->playLevelOption = LevelOption::HELL;
                            }

                            break;
                        case DifficultyLevelOption::HARD:
                            state->difficultyLevel = DifficultyLevel::HARD;
                            state->screen = Screen::PLAY_LEVEL;
                            state->pendingClear = true;
                            state->playDifficultyLevelOption = NORMAL;

                            if (state->unlockedLevel == Level::OVERWORLD) {
                                state->playLevelOption = LevelOption::OVERWORLD;
                            } else if (state->unlockedLevel == Level::MINES) {
                                state->playLevelOption = LevelOption::MINES;
                            } else if (state->unlockedLevel == Level::HELL) {
                                state->playLevelOption = LevelOption::HELL;
                            }

                            break;
                        case DifficultyLevelOption::BACK:
                            state->screen = Screen::MAIN_MENU;
                            state->pendingClear = true;
                            state->playDifficultyLevelOption = NORMAL;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->playDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->playDifficultyLevelOption = DifficultyLevelOption::BACK;
                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->playDifficultyLevelOption = DifficultyLevelOption::EASY;
                            break;
                        case DifficultyLevelOption::HARD:
                            state->playDifficultyLevelOption = DifficultyLevelOption::NORMAL;
                            break;
                        case DifficultyLevelOption::BACK:
                            state->playDifficultyLevelOption = DifficultyLevelOption::HARD;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->playDifficultyLevelOption) {
                        case DifficultyLevelOption::EASY:
                            state->playDifficultyLevelOption = DifficultyLevelOption::NORMAL;
                            break;
                        case DifficultyLevelOption::NORMAL:
                            state->playDifficultyLevelOption = DifficultyLevelOption::HARD;
                            break;
                        case DifficultyLevelOption::HARD:
                            state->playDifficultyLevelOption = DifficultyLevelOption::BACK;
                            break;
                        case DifficultyLevelOption::BACK:
                            state->playDifficultyLevelOption = DifficultyLevelOption::EASY;
                            break;
                    }
                }
                break;
            case Screen::PLAY_LEVEL:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->playLevelOption) {
                        case LevelOption::OVERWORLD:
                            state->level = Level::OVERWORLD;
                            state->screen = Screen::LOADING;
                            state->pendingClear = true;
                            state->pendingGenerate = true;
                            break;
                        case LevelOption::MINES:
                            if (state->unlockedLevel != Level::OVERWORLD) {
                                state->level = Level::MINES;
                                state->screen = Screen::LOADING;
                                state->pendingClear = true;
                                state->pendingGenerate = true;
                            }
                            break;
                        case LevelOption::HELL:
                            if (state->unlockedLevel == Level::HELL) {
                                state->level = Level::MINES;
                                state->screen = Screen::LOADING;
                                state->pendingClear = true;
                                state->pendingGenerate = true;
                            }
                            break;
                        case LevelOption::BACK:
                            if (!state->playedOnce) {
                                state->screen = Screen::PLAY_DIFFICULTY_LEVEL;
                            } else {
                                state->screen = Screen::MAIN_MENU;
                            }
                            state->pendingClear = true;

                            if (state->unlockedLevel == Level::OVERWORLD) {
                                state->playLevelOption = LevelOption::OVERWORLD;
                            } else if (state->unlockedLevel == Level::MINES) {
                                state->playLevelOption = LevelOption::MINES;
                            } else if (state->unlockedLevel == Level::HELL) {
                                state->playLevelOption = LevelOption::HELL;
                            }
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->playLevelOption) {
                        case LevelOption::OVERWORLD:
                            state->playLevelOption = LevelOption::BACK;
                            break;
                        case LevelOption::MINES:
                            state->playLevelOption = LevelOption::OVERWORLD;
                            break;
                        case LevelOption::HELL:
                            state->playLevelOption = LevelOption::MINES;
                            break;
                        case LevelOption::BACK:
                            state->playLevelOption = LevelOption::HELL;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->playLevelOption) {
                        case LevelOption::OVERWORLD:
                            state->playLevelOption = LevelOption::MINES;
                            break;
                        case LevelOption::MINES:
                            state->playLevelOption = LevelOption::HELL;
                            break;
                        case LevelOption::HELL:
                            state->playLevelOption = LevelOption::BACK;
                            break;
                        case LevelOption::BACK:
                            state->playLevelOption = LevelOption::OVERWORLD;
                            break;
                    }
                }
                break;
            case Screen::PAUSE_MENU:
                if (wasKeyPressed(VK_RETURN)) {
                    switch (state->pauseMenuOption) {
                        case PauseMenuOption::CONTINUE:
                            state->screen = Screen::GAME;
                            state->pendingClear = true;
                            break;
                        case PauseMenuOption::EXIT:
                            state->screen = Screen::MAIN_MENU;
                            state->pendingClear = true;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->pauseMenuOption) {
                        case PauseMenuOption::CONTINUE:
                            state->pauseMenuOption = PauseMenuOption::EXIT;
                            break;
                        case PauseMenuOption::EXIT:
                            state->pauseMenuOption = PauseMenuOption::CONTINUE;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->pauseMenuOption) {
                        case PauseMenuOption::CONTINUE:
                            state->pauseMenuOption = PauseMenuOption::EXIT;
                            break;
                        case PauseMenuOption::EXIT:
                            state->pauseMenuOption = PauseMenuOption::CONTINUE;
                            break;
                    }
                }
                break;
            case Screen::GAME:
                if (wasKeyPressed(VK_ESCAPE)) {
                    state->screen = Screen::PAUSE_MENU;
                    state->pendingClear = true;
                } else if (wasKeyPressed('Q')) {
                    auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                    switch (item->type) {
                        case ItemType::SWORD:
                            state->world[state->playerPosition.x][state->playerPosition.y].item.swap(state->sword);
                            break;
                        case ItemType::BOW:
                            state->world[state->playerPosition.x][state->playerPosition.y].item.swap(state->bow);
                            break;
                        case ItemType::ARMOR:
                            state->world[state->playerPosition.x][state->playerPosition.y].item.swap(state->armor);
                            break;
                    }
                } else if (wasKeyPressed('A')) {
                    if (
                            state->playerPosition.x > 0 &&
                            state->world[state->playerPosition.x - 1][state->playerPosition.y].type != BlockType::WALL
                            ) {
                        state->playerPosition.x--;

                        auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                        if (item->type == ItemType::ARROWS) {
                            auto transferable = (std::min)(state->maxArrows - state->arrows, item->count);
                            state->arrows += transferable;

                            if (transferable == item->count) {
                                state->world[state->playerPosition.x][state->playerPosition.y].item.reset();
                            } else {
                                state->world[state->playerPosition.x][state->playerPosition.y].item->count -= transferable;
                            }
                        }
                    }
                } else if (wasKeyPressed('W')) {
                    if (
                            state->playerPosition.y > 0 &&
                            state->world[state->playerPosition.x][state->playerPosition.y - 1].type != BlockType::WALL
                            ) {
                        state->playerPosition.y--;

                        auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                        if (item->type == ItemType::ARROWS) {
                            auto transferable = (std::min)(state->maxArrows - state->arrows, item->count);
                            state->arrows += transferable;

                            if (transferable == item->count) {
                                state->world[state->playerPosition.x][state->playerPosition.y].item.reset();
                            } else {
                                state->world[state->playerPosition.x][state->playerPosition.y].item->count -= transferable;
                            }
                        }
                    }
                } else if (wasKeyPressed('S')) {
                    if (
                            state->playerPosition.y < 1000 &&
                            state->world[state->playerPosition.x][state->playerPosition.y + 1].type != BlockType::WALL
                            ) {
                        state->playerPosition.y++;

                        auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                        if (item->type == ItemType::ARROWS) {
                            auto transferable = (std::min)(state->maxArrows - state->arrows, item->count);
                            state->arrows += transferable;

                            if (transferable == item->count) {
                                state->world[state->playerPosition.x][state->playerPosition.y].item.reset();
                            } else {
                                state->world[state->playerPosition.x][state->playerPosition.y].item->count -= transferable;
                            }
                        }
                    }
                } else if (wasKeyPressed('D')) {
                    if (
                            state->playerPosition.x < 1000 &&
                            state->world[state->playerPosition.x + 1][state->playerPosition.y].type != BlockType::WALL
                            ) {
                        state->playerPosition.x++;

                        auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                        if (item->type == ItemType::ARROWS) {
                            auto transferable = (std::min)(state->maxArrows - state->arrows, item->count);
                            state->arrows += transferable;

                            if (transferable == item->count) {
                                state->world[state->playerPosition.x][state->playerPosition.y].item.reset();
                            } else {
                                state->world[state->playerPosition.x][state->playerPosition.y].item->count -= transferable;
                            }
                        }
                    }
                }
                break;
        }
    }
}
