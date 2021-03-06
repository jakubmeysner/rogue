#include <thread>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "state.h"
#include "render.h"
#include "input.h"

int main() {
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

    auto renderThread = std::thread(render, &state);
    auto inputThread = std::thread(input, &state);

    renderThread.join();
    inputThread.join();

    clear();
    resetColor();
    setCursorVisibility(true);
}
