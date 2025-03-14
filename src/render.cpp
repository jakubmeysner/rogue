#include "render.h"

int WHITE_ON_BLACK = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
int BLACK_ON_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

int RED_ON_BLACK = FOREGROUND_RED;
int RED_ON_WHITE = FOREGROUND_RED | BLACK_ON_WHITE;
int RED_GREEN_ON_BLACK = FOREGROUND_RED | FOREGROUND_GREEN;
int BLUE_INTENSITY_ON_BLACK = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

void clear() {
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(handle, &bufferInfo);

    DWORD written;

    std::cout.flush();

    FillConsoleOutputCharacter(
            handle, TEXT(' '), bufferInfo.dwSize.X * bufferInfo.dwSize.Y,
            COORD{0, 0}, &written
    );

    FillConsoleOutputAttribute(
            handle, bufferInfo.wAttributes, bufferInfo.dwSize.X * bufferInfo.dwSize.Y,
            COORD{0, 0}, &written
    );

    SetConsoleCursorPosition(handle, COORD{0, 0});
}

void setCursorPosition(short x, short y) {
    std::cout.flush();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{x, y});
}

void setCursorVisibility(bool visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setColor(int color) {
    std::cout.flush();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(WHITE_ON_BLACK);
}

void render(State *state) {
    clear();
    resetColor();

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

    auto columns = bufferInfo.dwSize.X;
    auto lines = bufferInfo.dwSize.Y;

    while (true) {
        if (state->exit) break;

        if (state->pendingClear) {
            clear();
            state->pendingClear = false;
        }

        switch (state->screen) {
            case Screen::MAIN_MENU:
                setCursorPosition(columns / 2 - 3, lines / 2 - 4);
                std::cout << "ROGUE";

                setCursorPosition(columns / 2 - 2, lines / 2);
                if (state->mainMenuOption == MainMenuOption::PLAY) setColor(BLACK_ON_WHITE);
                std::cout << "Graj";
                resetColor();

                setCursorPosition(columns / 2 - 5, lines / 2 + 2);
                if (state->mainMenuOption == MainMenuOption::SETTINGS) setColor(BLACK_ON_WHITE);
                std::cout << "Ustawienia";
                resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 4);
                if (state->mainMenuOption == MainMenuOption::EXIT) setColor(BLACK_ON_WHITE);
                std::cout << "Wyjdź";
                resetColor();

                break;
            case Screen::SETTINGS:
                setCursorPosition(columns / 2 - 5, lines / 2 - 4);
                std::cout << "Ustawienia";

                setCursorPosition(columns / 2 - 11, lines / 2);
                if (state->settingsOption == SettingsOption::CHANGE_DIFFICULTY_LEVEL) setColor(BLACK_ON_WHITE);
                std::cout << "Zmień poziom trudności";
                resetColor();

                setCursorPosition(columns / 2 - 8, lines / 2 + 2);
                if (state->settingsOption == SettingsOption::RESET_PROGRESS) setColor(BLACK_ON_WHITE);
                std::cout << (state->recentlyResetProgress ? "ZRESETUJ POSTĘP" : "Zresetuj postęp");
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 4);
                if (state->settingsOption == SettingsOption::BACK) setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();

                break;
            case Screen::SETTINGS_DIFFICULTY_LEVEL:
                setCursorPosition(columns / 2 - 8, lines / 2 - 5);
                std::cout << "Poziom trudności";

                setCursorPosition(columns / 2 - 2, lines / 2 - 1);
                if (state->settingsDifficultyLevelOption == DifficultyLevelOption::EASY)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::EASY ? "ŁATWY" : "Łatwy");
                resetColor();

                setCursorPosition(columns / 2 - 4, lines / 2 + 1);
                if (state->settingsDifficultyLevelOption == DifficultyLevelOption::NORMAL)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::NORMAL ? "NORMALNY" : "Normalny");
                resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 3);
                if (state->settingsDifficultyLevelOption == DifficultyLevelOption::HARD)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::HARD ? "TRUDNY" : "Trudny");
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 5);
                if (state->settingsDifficultyLevelOption == DifficultyLevelOption::BACK)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();
                break;
            case Screen::PLAY_DIFFICULTY_LEVEL:
                setCursorPosition(columns / 2 - 8, lines / 2 - 5);
                std::cout << "Poziom trudności";

                setCursorPosition(columns / 2 - 2, lines / 2 - 1);
                if (state->playDifficultyLevelOption == DifficultyLevelOption::EASY)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Łatwy";
                resetColor();

                setCursorPosition(columns / 2 - 4, lines / 2 + 1);
                if (state->playDifficultyLevelOption == DifficultyLevelOption::NORMAL)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Normalny";
                resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 3);
                if (state->playDifficultyLevelOption == DifficultyLevelOption::HARD)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Trudny";
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 5);
                if (state->playDifficultyLevelOption == DifficultyLevelOption::BACK)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();
                break;
            case Screen::PLAY_LEVEL:
                setCursorPosition(columns / 2 - 3, lines / 2 - 5);
                std::cout << "Poziom";

                setCursorPosition(columns / 2 - 6, lines / 2 - 1);
                if (state->playLevelOption == LevelOption::OVERWORLD) setColor(BLACK_ON_WHITE);
                std::cout << "Powierzchnia";
                resetColor();

                setCursorPosition(columns / 2 - 4, lines / 2 + 1);
                if (state->unlockedLevel == Level::OVERWORLD) {
                    if (state->playLevelOption == LevelOption::MINES) {
                        setColor(RED_ON_WHITE);
                    } else {
                        setColor(RED_ON_BLACK);
                    }
                } else if (state->playLevelOption == LevelOption::MINES) {
                    setColor(BLACK_ON_WHITE);
                }
                std::cout << "Kopalnie";
                resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 3);
                if (state->unlockedLevel != Level::HELL) {
                    if (state->playLevelOption == LevelOption::HELL) {
                        setColor(RED_ON_WHITE);
                    } else {
                        setColor(RED_ON_BLACK);
                    }
                } else if (state->playLevelOption == LevelOption::HELL) {
                    setColor(BLACK_ON_WHITE);
                }
                std::cout << "Piekło";
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 5);
                if (state->playLevelOption == LevelOption::BACK) setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();

                break;
            case Screen::LOADING:
                setCursorPosition(columns / 2 - 6, lines / 2);
                std::cout << "Ładowanie...";

//                setColor(RED_ON_BLACK);
//                setCursorPosition(columns / 2 - 4, lines / 2 + 2);
//                std::cout << "AMOGUSA";
//                setCursorPosition(columns / 2 - 4, lines / 2 + 3);
//                std::cout << "MO   GU";
//                setCursorPosition(columns / 2 - 4, lines / 2 + 4);
//                std::cout << "SAMOGUS";
//                setCursorPosition(columns / 2 - 4, lines / 2 + 5);
//                std::cout << "AMOGUSA";
//                setCursorPosition(columns / 2 - 4, lines / 2 + 6);
//                std::cout << "MO   GU";
//                resetColor();

                {
                    setCursorPosition(columns / 2 - 15, lines / 2 + 2);
                    std::cout << "⡯⡯⡾⠝⠘⠀   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢊⠘⡮⣣⠪⠢⡑⡌ ㅤ";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 3);
                    std::cout << "⠟⠝⠈⠀⠀⠀.  ⠡⠀⠠⢈⠠⢐⢠⢂⢔⣐⢄⡂⢔⠀⡁⢉⠸⢨⢑⠕⡌ ㅤ ⠀";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 4);
                    std::cout << "⠀ ⡀⠁⠀⠀⠀⡀⢂⠡⠈⡔⣕⢮⣳⢯⣿⣻⣟⣯⣯⢷⣫⣆⡂  ⢐⠑⡌";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 5);
                    std::cout << "⢀⠠⠐⠈⠀⢀⢂⠢⡂⠕⡁⣝⢮⣳⢽⡽⣾⣻⣿⣯⡯⣟⣞⢾⢜⢆⠀⡀⠀⠪";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 6);
                    std::cout << "⣬⠂⠀⠀⢀⢂⢪⠨⢂⠥⣺⡪⣗⢗⣽⢽⡯⣿⣽⣷⢿⡽⡾⡽⣝⢎⠀⠀⠀⢡";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 7);
                    std::cout << "⣿⠀⠀⠀⢂⠢⢂⢥⢱⡹⣪⢞⡵⣻⡪⡯⡯⣟⡾⣿⣻⡽⣯⡻⣪⠧⠑⠀⠁⢐";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 8);
                    std::cout << "⣿⠀⠀⠀⠢⢑⠠⠑⠕⡝⡎⡗⡝⡎⣞⢽⡹⣕⢯⢻⠹⡹⢚⠝⡷⡽⡨⠀⠀⢔";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 9);
                    std::cout << "⣿⡯⠀⢈⠈⢄⠂⠂⠐⠀⠌⠠⢑⠱⡱⡱⡑⢔⠁⠀⡀⠐⠐⠐⡡⡹⣪⠀⠀⢘";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 10);
                    std::cout << "⣿⣽⠀⡀⡊⠀⠐⠨⠈⡁⠂⢈⠠⡱⡽⣷⡑⠁⠠⠑⠀⢉⢇⣤⢘⣪⢽⠀⢌⢎";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 11);
                    std::cout << "⣿⢾⠀⢌⠌⠀⡁⠢⠂⠐⡀⠀⢀⢳⢽⣽⡺⣨⢄⣑⢉⢃⢭⡲⣕⡭⣹⠠⢐⢗";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 12);
                    std::cout << "⣿⡗⠀⠢⠡⡱⡸⣔⢵⢱⢸⠈⠀⡪⣳⣳⢹⢜⡵⣱⢱⡱⣳⡹⣵⣻⢔⢅⢬⡷";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 13);
                    std::cout << "⣷⡇⡂⠡⡑⢕⢕⠕⡑⠡⢂⢊⢐⢕⡝⡮⡧⡳⣝⢴⡐⣁⠃⡫⡒⣕⢏⡮⣷⡟";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 14);
                    std::cout << "⣷⣻⣅⠑⢌⠢⠁⢐⠠⠑⡐⠐⠌⡪⠮⡫⠪⡪⡪⣺⢸⠰⠡⠠⠐⢱⠨⡪⡪⡰";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 15);
                    std::cout << "⣯⢷⣟⣇⡂⡂⡌⡀⠀⠁⡂⠅⠂⠀⡑⡄⢇⠇⢝⡨⡠⡁⢐⠠⢀⢪⡐⡜⡪⡊";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 16);
                    std::cout << "⣿⢽⡾⢹⡄⠕⡅⢇⠂⠑⣴⡬⣬⣬⣆⢮⣦⣷⣵⣷⡗⢃⢮⠱⡸⢰⢱⢸⢨⢌";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 17);
                    std::cout << "⣯⢯⣟⠸⣳⡅⠜⠔⡌⡐⠈⠻⠟⣿⢿⣿⣿⠿⡻⣃⠢⣱⡳⡱⡩⢢⠣⡃⠢⠁";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 18);
                    std::cout << "⡯⣟⣞⡇⡿⣽⡪⡘⡰⠨⢐⢀⠢⢢⢄⢤⣰⠼⡾⢕⢕⡵⣝⠎⢌⢪⠪⡘⡌⠀";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 19);
                    std::cout << "⡯⣳⠯⠚⢊⠡⡂⢂⠨⠊⠔⡑⠬⡸⣘⢬⢪⣪⡺⡼⣕⢯⢞⢕⢝⠎⢻⢼⣀⠀";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 20);
                    std::cout << "⠁⡂⠔⡁⡢⠣⢀⠢⠀⠅⠱⡐⡱⡘⡔⡕⡕⣲⡹⣎⡮⡏⡑⢜⢼⡱⢩⣗⣯⣟";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 21);
                    std::cout << "⢀⢂⢑⠀⡂⡃⠅⠊⢄⢑⠠⠑⢕⢕⢝⢮⢺⢕⢟⢮⢊⢢⢱⢄⠃⣇⣞⢞⣞⢾";
                    setCursorPosition(columns / 2 - 15, lines / 2 + 22);
                    std::cout << "⢀⠢⡑⡀⢂⢊⠠⠁⡂⡐⠀⠅⡈⠪⠪⠪⠣⠫⠑⡁⢔⠕⣜⣜⢦⡰⡎⡯⡾⡽";
                }

                break;
            case Screen::PAUSE_MENU:
                setCursorPosition(columns / 2 - 5, lines / 2 - 3);
                std::cout << "Spauzowano";

                setCursorPosition(columns / 2 - 4, lines / 2 + 1);
                if (state->pauseMenuOption == PauseMenuOption::CONTINUE) setColor(BLACK_ON_WHITE);
                std::cout << "Kontynuuj";
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 3);
                if (state->pauseMenuOption == PauseMenuOption::EXIT) setColor(BLACK_ON_WHITE);
                std::cout << "Wyjdź";
                resetColor();

                break;
            case Screen::GAME:
                auto fov = (
                        state->difficultyLevel == DifficultyLevel::NORMAL ?
                        48 : (state->difficultyLevel == DifficultyLevel::EASY ? 64 : 32)
                );

                auto cStart = (columns - fov) / 2;
                auto cStartPos = state->playerPosition.x - fov / 2;
                auto cEnd = (columns + fov) / 2;
                auto lStart = (lines - fov) / 2;
                auto lStartPos = state->playerPosition.y - fov / 2;
                auto lEnd = (lines + fov) / 2;

                for (int c = cStart; c <= cEnd; c++) {
                    for (int l = lStart; l <= lEnd; l++) {
                        setCursorPosition(c, l);

                        if (l == lStart || l == lEnd) {
                            std::cout << "-";
                        } else if (c == cStart || c == cEnd) {
                            std::cout << "|";
                        } else {
                            if (c == columns / 2 && l == lines / 2) {
                                setColor(BLUE_INTENSITY_ON_BLACK);
                                std::cout << "p";
                                resetColor();
                            } else {
                                auto x = cStartPos - cStart + c;
                                auto y = lStartPos - lStart + l;

                                if (x >= 0 && x <= 1000 && y >= 0 && y <= 1000) {
                                    auto entity = std::find_if(
                                            std::begin(state->entities), std::end(state->entities),
                                            [x, y](Entity entity) {
                                                return entity.position.x == x && entity.position.y == y;
                                            }
                                    );

                                    if (entity != std::end(state->entities)) {
                                        switch ((*entity).type) {
                                            case EntityType::ZOMBIE:
                                                std::cout << "z";
                                                break;
                                            case EntityType::ARCHER:
                                                std::cout << "a";
                                                break;
                                            case EntityType::BOOMER:
                                                std::cout << "b";
                                                break;
                                            default:
                                                std::cout << "t";
                                        }
                                    } else if (state->world[x][y].item.has_value()) {
                                        std::cout << "i";
                                    } else {
                                        switch (state->world[x][y].type) {
                                            case BlockType::WALL:
                                                setColor(BLACK_ON_WHITE);
                                                std::cout << "W";
                                                resetColor();
                                                break;
                                            case BlockType::DOOR:
                                                setColor(RED_GREEN_ON_BLACK);
                                                std::cout << "D";
                                                resetColor();
                                                break;
                                            default:
                                                std::cout << " ";
                                        }
                                    }
                                } else {
                                    std::cout << " ";
                                }
                            }
                        }
                    }
                }

                setCursorPosition(cEnd + 4, lStart + 1);
                std::cout << "Zdrowie:   " << state->health << "/" << state->maxHealth << "          ";

                setCursorPosition(cEnd + 4, lStart + 2);
                std::cout << "Kondycja:  " << state->stamina << "/" << state->maxStamina << "          ";

                setCursorPosition(cEnd + 4, lStart + 4);
                std::cout << "Klucze:    " << state->keys << "/3";

                setCursorPosition(cEnd + 4, lStart + 6);
                std::cout << "Miecz:     " << (state->sword.has_value() ? state->sword->getShortInfo() : "(Brak)")
                          << "          ";

                setCursorPosition(cEnd + 4, lStart + 7);
                std::cout << "Łuk:       " << (state->bow.has_value() ? state->bow->getShortInfo() : "(Brak)")
                          << "          ";

                setCursorPosition(cEnd + 4, lStart + 8);
                std::cout << "Zbroja:    " << (state->armor.has_value() ? state->armor->getShortInfo() : "(Brak)")
                          << "          ";

                setCursorPosition(cEnd + 4, lStart + 9);
                std::cout << "Strzały:   " << state->arrows << "/" << state->maxArrows << "          ";

                setCursorPosition(cEnd + 4, lStart + 11);
                std::cout << "Przedmiot: ";

                auto item = state->world[state->playerPosition.x][state->playerPosition.y].item;

                if (item.has_value()) {
                    switch (item->type) {
                        case ItemType::SWORD:
                            std::cout << "Miecz";
                            break;
                        case ItemType::BOW:
                            std::cout << "Łuk";
                            break;
                        case ItemType::ARMOR:
                            std::cout << "Zbroja";
                            break;
                        case ItemType::ARROWS:
                            std::cout << "Strzały";
                            break;
                    }

                    std::cout << " " << item->getShortInfo();
                } else {
                    std::cout << "Brak";
                }

                std::cout << "                              ";

                break;
        }
    }
}
