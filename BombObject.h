#ifndef BOMB_OBJECT_H_
#define BOMB_OBJECT_H_
#include "BaseObject.h"
#include "CommonFunc.h"
#include "map.h"
class BombObject:public BaseObject
{
public :
    BombObject();
    ~BombObject();
    void SetClip();
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetFrame(int x)
    {
        frame_=x;
    }
    int getframe()
    {
        return frame_;
    }
    void SetClipBom();
    bool getbomno1()
    {
        return bom_no;
    }
    void SetBomno(bool t)
    {
        bom_no=t;
    }
    void ShowBomNoMiddle(SDL_Renderer* screen, Map &map_data_);
    void ShowBomNoLeft(SDL_Renderer* screen, Map &map_data_);
    void ShowBomNoRight(SDL_Renderer* screen, Map &map_data);
    void ShowBomNoUp(SDL_Renderer* screen, Map &map_data_);
    void ShowBomNoDown(SDL_Renderer* screen, Map &map_data_);
    void logicbomno(Map& map_data,GameMap& game_map);

private:
    SDL_Rect clip_[5];
    int frame_;
    int bomb_width;
    int bomb_height;
    bool bom_no;
    SDL_Rect clip_bom_no[5];
    int logicx;
    int logicy;
};
#endif // BOMB_OBJECT_H_

