#include <random>
#include "generate.h"

World generateOverworld(State *state) {
    World world;

    world.resize(1000);

    for (auto &c: world) {
        c.resize(1000);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution buildingDistrib(0.005);
    std::uniform_int_distribution buildingSizeDistrib(6, 12);

    for (int c = 50; c < 950; c++) {
        for (int l = 50; l < 950; l++) {
            if (buildingDistrib(gen)) {
                auto cSize = buildingSizeDistrib(gen);
                auto lSize = buildingSizeDistrib(gen);

                for (int cDif = -3; cDif <= cSize + 3; cDif++) {
                    for (int lDif = -3; lDif <= lSize + 3; lDif++) {
                        if (world[c + cDif][l + lDif].type != BlockType::EMPTY) goto l;
                        if (state->playerPosition.x == c + cDif || state->playerPosition.y == l + lDif) goto l;
                    }
                }

                std::uniform_int_distribution doorWallDistrib(1, 4);
                auto doorWall = doorWallDistrib(gen);
                std::uniform_int_distribution doorWallElemDistrib(1, (doorWall <= 2 ? lSize - 2 : cSize - 2));
                auto doorWallElem = doorWallElemDistrib(gen);

                for (int cBuild = 0; cBuild < cSize; cBuild++) {
                    for (int lBuild = 0; lBuild < lSize; lBuild++) {
                        if ((cBuild == 0 || cBuild == cSize - 1) && (lBuild == 0 || lBuild == lSize - 1)) {
                            world[c + cBuild][l + lBuild].type = BlockType::WALL;
                        } else if (cBuild == 0 || cBuild == cSize - 1 || lBuild == 0 || lBuild == lSize - 1) {
                            if (
                                    (doorWall == 1 && cBuild == 0 && lBuild == doorWallElem) ||
                                    (doorWall == 2 && cBuild == cSize - 1 && lBuild == doorWallElem) ||
                                    (doorWall == 3 && lBuild == 0 && cBuild == doorWallElem) ||
                                    (doorWall == 4 && lBuild == lSize - 1 && cBuild == doorWallElem)
                                    ) {
                                world[c + cBuild][l + lBuild].type = BlockType::DOOR;
                            } else {
                                world[c + cBuild][l + lBuild].type = BlockType::WALL;
                            }
                        } else {
                            world[c + cBuild][l + lBuild].type = BlockType::EMPTY_INSIDE;
                        }
                    }
                }
            }

            l:;
        }
    }

    return world;
}

World generateMines(State *state) {
    World world;

    world.resize(1000);

    for (auto &l: world) {
        l.resize(1000);
    }

    return world;
}

World generateHell(State *state) {
    World world;

    world.resize(1000);

    for (auto &l: world) {
        l.resize(1000);
    }

    return world;
}

void generate(State *state) {
    while (true) {
        if (state->exit) break;

        if (state->pendingGenerate) {
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<int> playerPosDistrib(100, 900);
            state->playerPosition = Position(playerPosDistrib(gen), playerPosDistrib(gen));

            switch (state->level) {
                case Level::OVERWORLD:
                    state->world = generateOverworld(state);
                    break;
                case Level::MINES:
                    state->world = generateMines(state);
                    break;
                case Level::HELL:
                    state->world = generateHell(state);
                    break;
            }

            int health = 10;
            int maxHealth = 10;
            int stamina = 10;
            int maxStamina = 10;

            state->pendingGenerate = false;
            state->screen = Screen::GAME;
            state->pendingClear = true;

            if (!state->playedOnce) {
                state->playedOnce = true;
                state->pendingSave = true;
            }
        }
    }
}
