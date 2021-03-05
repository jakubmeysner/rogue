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
                        case SettingsOption::RESET_PROGRESS:

                            break;
                        case SettingsOption::BACK:
                            state->screen = Screen::MAIN_MENU;
                            state->changedScreen = true;
                            state->settingsOption = SettingsOption::RESET_PROGRESS;
                            break;
                    }
                } else if (wasKeyPressed(VK_UP)) {
                    switch (state->settingsOption) {
                        case SettingsOption::RESET_PROGRESS:
                            state->settingsOption = SettingsOption::BACK;
                            break;
                        case SettingsOption::BACK:
                            state->settingsOption = SettingsOption::RESET_PROGRESS;
                            break;
                    }
                } else if (wasKeyPressed(VK_DOWN)) {
                    switch (state->settingsOption) {
                        case SettingsOption::RESET_PROGRESS:
                            state->settingsOption = SettingsOption::BACK;
                            break;
                        case SettingsOption::BACK:
                            state->settingsOption = SettingsOption::RESET_PROGRESS;
                            break;
                    }
                }
                break;
        }
    }
}
