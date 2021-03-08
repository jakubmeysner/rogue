#include <map>
#include <fstream>
#include <filesystem>
#include "save.h"

auto saveDirPath = std::string(std::getenv("LOCALAPPDATA")) + "\\Rogue";
auto saveFilePath = saveDirPath + "\\save.txt";

void saveState(State *state) {
    auto saveFile = std::ofstream(saveFilePath);

    if (state->playedOnce) {
        saveFile << "playedOnce true\n";
    } else {
        saveFile << "playedOnce false\n";
    }

    if (state->difficultyLevel == DifficultyLevel::EASY) {
        saveFile << "difficultyLevel easy\n";
    } else if (state->difficultyLevel == DifficultyLevel::NORMAL) {
        saveFile << "difficultyLevel normal\n";
    } else if (state->difficultyLevel == DifficultyLevel::HARD) {
        saveFile << "difficultyLevel hard\n";
    }

    if (state->unlockedLevel == Level::OVERWORLD) {
        saveFile << "unlockedLevel overworld\n";
    } else if (state->unlockedLevel == Level::MINES) {
        saveFile << "unlockedLevel mines\n";
    } else if (state->unlockedLevel == Level::HELL) {
        saveFile << "unlockedLevel hell\n";
    }

    saveFile.close();
}

void save(State *state) {
    if (!std::filesystem::exists(saveDirPath)) {
        std::filesystem::create_directory(saveDirPath);
    }

    if (!std::filesystem::exists(saveFilePath)) {
        auto defaultFile = std::ofstream(saveFilePath);
        defaultFile.close();
    }

    auto loadFile = std::ifstream(saveFilePath);

    std::map<std::string, std::string> data;
    std::string key;
    std::string value;

    while (loadFile >> key && loadFile >> value) {
        data[key] = value;
    }

    loadFile.close();

    if (data["playedOnce"] == "true") {
        state->playedOnce = true;
    }

    if (data["difficultyLevel"] == "easy") {
        state->difficultyLevel = DifficultyLevel::EASY;
    } else if (data["difficultyLevel"] == "hard") {
        state->difficultyLevel = DifficultyLevel::HARD;
    }

    if (data["unlockedLevel"] == "mines") {
        state->unlockedLevel = Level::MINES;
    } else if (data["unlockedLevel"] == "hell") {
        state->unlockedLevel = Level::HELL;
    }

    state->initialLoadPerformed = true;

    while (true) {
        if (state->exit) break;

        if (state->pendingSave) {
            saveState(state);
            state->pendingSave = false;
        }
    }

    saveState(state);
}
