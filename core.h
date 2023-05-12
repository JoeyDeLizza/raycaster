#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/types.h>
#include <vector>
#include <cstdint>
#include <cassert>
#include "graphics.h"
#include "map.h"
#include "SDL2/SDL.h"
#include "lineseg.h"

void initialize(SDL_Window **w, SDL_Renderer **r, SDL_Surface **s, SDL_Texture **t);
