#ifndef MAP_H_
#define MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Support.h"

#define MAX_TILES 5
class TileMap : public BaseObject
{
public:
    TileMap() {;}
    ~TileMap() {;}
};
class Tile_Threat : public BaseObject
{
public:
    Tile_Threat() {;}
    ~Tile_Threat() {;}
    SDL_Rect GetRectmThreat()
    {
        return rect_;
    }
    void deletetile()
    {
        rect_.x=0;
        rect_.y=0;
        rect_.w=0;
        rect_.h=0;
    }
};
class GameMap: public BaseObject
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen, Support& win, Map& map_data);
    Map getMap()const
    {
        return game_map_;
    };
    Tile_Threat* gettile()
    {
        return tilethreat;
    }
    void setlaimap(Map& map_data)
    {
        game_map_=map_data;
    }
    void freetile_threat()
    {
        delete [] tilethreat;
    }

private:
    Tile_Threat *tilethreat = new Tile_Threat[100];
    Map game_map_;
    TileMap tile_map[MAX_TILES];
};
#endif // MAP_H_
