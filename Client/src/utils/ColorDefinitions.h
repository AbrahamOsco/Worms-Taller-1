//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_COLORDEFINITIONS_H
#define WORMS_TALLER_1_COLORDEFINITIONS_H

#include <map>
#include "SDL2pp/SDL2pp.hh"


enum ColorID {
    COLOR_RED = 0,
    COLOR_GREEN = 1,
    COLOR_BLUE = 2,
    COLOR_CUSTOM = 100
};

extern std::map<ColorID, SDL_Color> colorMap;

#endif  // WORMS_TALLER_1_COLORDEFINITIONS_H
