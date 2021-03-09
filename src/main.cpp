#include <thread>
#include <vector>
#include <iostream>
#include <windows.h>
#include "state.h"
#include "save.h"
#include "render.h"
#include "input.h"
#include "generate.h"

int main() {
    SetConsoleTitle("Rogue");
    PlaySound(".\\assets\\amogus-drip.wav", nullptr, SND_ASYNC | SND_FILENAME | SND_LOOP);

    SetConsoleOutputCP(65001);

    while (true) {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

        if (bufferInfo.dwSize.X >= 150 && bufferInfo.dwSize.Y >= 30) break;

        std::cout << "Zwiększ rozmiar okna do min. 150x30 (aktualny " << bufferInfo.dwSize.X << "x"
                  << bufferInfo.dwSize.Y << "), a następnie naciśnij ENTER!" << std::endl;

        while (!wasKeyPressed(VK_RETURN));
    }

    setCursorVisibility(false);

    auto state = State();

    auto saveThread = std::thread(save, &state);

    while (!state.initialLoadPerformed);

    auto renderThread = std::thread(render, &state);
    auto inputThread = std::thread(input, &state);
    auto generateThread = std::thread(generate, &state);

    saveThread.join();
    renderThread.join();
    inputThread.join();
    generateThread.join();

    clear();
    resetColor();
    setCursorVisibility(true);

    std::cout << "Naciśnij Ctrl+C, aby zakończyć." << std::endl;
    std::cin.ignore(INT_MAX);
    clear();
}
