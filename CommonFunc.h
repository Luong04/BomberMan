#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>

const int dx[5] = {-1,0,1,0,0};
const int dy[5] = {0,-1,0,1,0};

const int LEVEL_WIDTH = 2310;
const int LEVEL_HEIGHT = 1540;
const int SCREEN_WIDTH = 1190;
const int SCREEN_HEIGHT = 770;

static const int DOT_WIDTH = 66;
static const int DOT_HEIGHT = 67;
static bool CHECK = true;
static const int RND = 53;
static bool mute = false;

struct Input
{
    int left;
    int right;
    int up;
    int down;
};

#define TILE_SIZE 70
#define MAP_X 33
#define MAP_Y 22

struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAP_Y][MAP_X];
    char *file_name;
};

namespace SDLCommonFunc
{
bool CheckFocusWithRect(const int &x, const int &y,const SDL_Rect &rect);
bool CheckCollision(const SDL_Rect& obj1,const SDL_Rect& obj2);
bool CheckCollision1(const SDL_Rect& obj1,const SDL_Rect& obj2);
}
#endif // COMMON_FUNC_H_
