#pragma once

#include <iostream>
#include <windows.h>
#include "state.h"

void clear();

void setCursorPosition(short x, short y);

void setCursorVisibility(bool visible);

void setColor(int color);

void resetColor();

void render(State *state);
