#pragma once

#include <iostream>
#include <windows.h>
#include "state.h"

void clear();

void setCursorVisibility(bool visible);

void resetColor();

void render(State *state);
