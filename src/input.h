#pragma once

#include <windows.h>
#include <bitset>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "state.h"

bool wasKeyPressed(int key);

void input(State *state);
