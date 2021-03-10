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

    std::bernoulli_distribution itemDistrib(
            (state->difficultyLevel == DifficultyLevel::NORMAL ? 0.03 : (state->difficultyLevel ==
                                                                         DifficultyLevel::EASY) ? 0.05 : 0.01));
    std::uniform_int_distribution itemTypeDistrib(1, 4);
    std::normal_distribution<> swordDamageDistrib(15, 5);
    std::normal_distribution<> swordSweepDistrib(20, 10);
    std::normal_distribution<> bowDamageDistrib(10, 5);
    std::normal_distribution<> bowRangeDistrib(10, 5);
    std::normal_distribution<> armorProtDistrib(45, 15);
    std::normal_distribution<> armorCritProtDistrib(20, 10);
    std::normal_distribution<> durabilityDistrib(20, 10);
    std::normal_distribution<> arrowCountDistrib(3, 2);

    for (int c = 50; c < 950; c++) {
        for (int l = 50; l < 950; l++) {
            if (world[c][l].type == BlockType::EMPTY_INSIDE && itemDistrib(gen)) {
                auto item = Item();

                switch (itemTypeDistrib(gen)) {
                    case 1:
                        item.type = ItemType::SWORD;
                        item.damage = std::max((int) swordDamageDistrib(gen), 1);
                        item.sweep = std::max(((double) (int) swordSweepDistrib(gen) / 100), 0.1);
                        item.durability = std::max((int) durabilityDistrib(gen), 1);
                        break;
                    case 2:
                        item.type = ItemType::BOW;
                        item.damage = std::max((int) bowDamageDistrib(gen), 1);
                        item.range = std::max((int) bowRangeDistrib(gen), 1);
                        item.durability = std::max((int) durabilityDistrib(gen), 1);
                        break;
                    case 3:
                        item.type = ItemType::ARMOR;
                        item.protection = std::max(((double) (int) armorProtDistrib(gen) / 100), 0.1);
                        item.criticalProtection = std::max(((double) (int) armorCritProtDistrib(gen) / 100), 0.1);
                        break;
                    case 4:
                        item.type = ItemType::ARROWS;
                        item.count = std::min((int) arrowCountDistrib(gen), 1);
                        break;
                }

                world[c][l].item = item;
            }
        }
    }

    std::bernoulli_distribution zombieDistrib(0.001);

    std::bernoulli_distribution archerDistrib(0.0005);

    std::bernoulli_distribution boomerDistrib(0.0001);

    for (int c = 0; c < 1000; c++) {
        for (int l = 0; l < 1000; l++) {
            if (world[c][l].type == BlockType::EMPTY) {
                if (zombieDistrib(gen)) {
                    auto entity = Entity();
                    entity.type = EntityType::ZOMBIE;
                    entity.position = Position(c, l);
                    state->entities.push_back(entity);
                } else if (archerDistrib(gen)) {
                    auto entity = Entity();
                    entity.type = EntityType::ARCHER;
                    entity.position = Position(c, l);
                    state->entities.push_back(entity);
                } else if (boomerDistrib(gen)) {
                    auto entity = Entity();
                    entity.type = EntityType::BOOMER;
                    entity.position = Position(c, l);
                    state->entities.push_back(entity);
                }
            }
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

            state->entities.clear();

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

            state->health = 10;
            state->maxHealth = 10;
            state->stamina = 10;
            state->maxStamina = 10;

            state->sword.reset();
            state->bow.reset();
            state->armor.reset();

            state->arrows = 0;
            state->maxArrows = 5;

            state->keys = 0;

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
