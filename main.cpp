#include <thread>
#include <vector>
#include <iostream>
#include <bitset>
#include <windows.h>

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

auto WHITE_ON_BLACK = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
auto BLACK_ON_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

void setColor(unsigned short color) {
    std::cout.flush();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(WHITE_ON_BLACK);
}

bool wasKeyPressed(int key) {
    auto keyState = GetAsyncKeyState(key);
    return keyState != 0 && std::bitset<sizeof(short)>(keyState)[0] == 1;
}

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
                if (state->mainMenuOption == MainMenuOption::PLAY) resetColor();

                setCursorPosition(columns / 2 - 5, lines / 2 + 2);
                if (state->mainMenuOption == MainMenuOption::SETTINGS) setColor(BLACK_ON_WHITE);
                std::cout << "Ustawienia";
                if (state->mainMenuOption == MainMenuOption::SETTINGS) resetColor();

                setCursorPosition(columns / 2 - 3, lines / 2 + 4);
                if (state->mainMenuOption == MainMenuOption::EXIT) setColor(BLACK_ON_WHITE);
                std::cout << "Wyjdź";
                resetColor();

                break;
            case Screen::SETTINGS:
                setCursorPosition(columns / 2 - 5, lines / 2 - 3);
                std::cout << "Ustawienia";

                setCursorPosition(columns / 2 - 8, lines / 2 + 1);
                if (state->settingsOption == SettingsOption::RESET_PROGRESS) setColor(BLACK_ON_WHITE);
                std::cout << "Zresetuj postęp";
                if (state->settingsOption == SettingsOption::RESET_PROGRESS) resetColor();

                setCursorPosition(columns / 2 - 2, lines / 2 + 3);
                if (state->settingsOption == SettingsOption::BACK) setColor(BLACK_ON_WHITE);
                std::cout << "Wróć";
                if (state->settingsOption == SettingsOption::BACK) resetColor();

                break;
        }
    }
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

int main() {
    SetConsoleOutputCP(65001);

    while (true) {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

        if (bufferInfo.dwSize.X >= 175 && bufferInfo.dwSize.Y >= 50) break;

        std::cout << "Zwiększ rozmiar okna do min. 175x50 (aktualny " << bufferInfo.dwSize.X << "x"
                  << bufferInfo.dwSize.Y << "), a następnie naciśnij ENTER!" << std::endl;

        while (!wasKeyPressed(VK_RETURN));
    }

    setCursorVisibility(false);

    auto state = State();

    auto renderThread = std::thread(render, &state);
    auto inputThread = std::thread(input, &state);

    renderThread.join();
    inputThread.join();

    clear();
    resetColor();
    setCursorVisibility(true);
}
