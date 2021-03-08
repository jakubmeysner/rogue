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

                            break;
                        case MainMenuOption::SETTINGS:
                            state->screen = Screen::SETTINGS;
                            state->changedScreen = true;
                            state->mainMenuOption = MainMenuOption::PLAY;
                            break;
                        case MainMenuOption::EXIT:
                            state->exit = true;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->mainMenuOption) {
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
                            state->changedScreen = true;
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
                            state->changedScreen = true;
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
                        case SettingsDifficultyLevelOption::EASY:
                            state->difficultyLevel = DifficultyLevel::EASY;
                            break;
                        case SettingsDifficultyLevelOption::NORMAL:
                            state->difficultyLevel = DifficultyLevel::NORMAL;
                            break;
                        case SettingsDifficultyLevelOption::HARD:
                            state->difficultyLevel = DifficultyLevel::HARD;
                            break;
                        case SettingsDifficultyLevelOption::BACK:
                            state->screen = Screen::SETTINGS;
                            state->changedScreen = true;
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::EASY;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->settingsDifficultyLevelOption) {
                        case SettingsDifficultyLevelOption::EASY:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::BACK;
                            break;
                        case SettingsDifficultyLevelOption::NORMAL:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::EASY;
                            break;
                        case SettingsDifficultyLevelOption::HARD:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::NORMAL;
                            break;
                        case SettingsDifficultyLevelOption::BACK:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::HARD;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->settingsDifficultyLevelOption) {
                        case SettingsDifficultyLevelOption::EASY:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::NORMAL;
                            break;
                        case SettingsDifficultyLevelOption::NORMAL:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::HARD;
                            break;
                        case SettingsDifficultyLevelOption::HARD:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::BACK;
                            break;
                        case SettingsDifficultyLevelOption::BACK:
                            state->settingsDifficultyLevelOption = SettingsDifficultyLevelOption::EASY;
                            break;
                    }
                }
                break;
        }
    }
}
