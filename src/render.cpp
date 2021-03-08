#include "render.h"

int WHITE_ON_BLACK = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
int BLACK_ON_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

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

        if (state->changedScreen) {
            clear();
            state->changedScreen = false;
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
                std::cout << "Zresetuj postęp";
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 4);
                if (state->settingsOption == SettingsOption::BACK) setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();

                break;
            case Screen::SETTINGS_DIFFICULTY_LEVEL:
                setCursorPosition(columns / 2 - 8, lines / 2 - 5);
                std::cout << "Poziom trudności";

                setCursorPosition(columns / 2 - 3, lines / 2 - 1);
                if (state->settingsDifficultyLevelOption == SettingsDifficultyLevelOption::EASY)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::EASY ? "ŁATWY" : "Łatwy");
                resetColor();

                setCursorPosition(columns / 2 - 4, lines / 2 + 1);
                if (state->settingsDifficultyLevelOption == SettingsDifficultyLevelOption::NORMAL)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::NORMAL ? "NORMALNY" : "Normalny");
                resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 3);
                if (state->settingsDifficultyLevelOption == SettingsDifficultyLevelOption::HARD)
                    setColor(BLACK_ON_WHITE);
                std::cout << (state->difficultyLevel == DifficultyLevel::HARD ? "TRUDNY" : "Trudny");
                resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 5);
                if (state->settingsDifficultyLevelOption == SettingsDifficultyLevelOption::BACK)
                    setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                resetColor();
        }
    }
}
