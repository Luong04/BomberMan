
#ifndef THREAT_H_
#define THREAT_H_
#include "CommonFunc.h"
#include "map.h"
#include "BaseObject.h"
class Threat:public BaseObject
{
public:
    Threat();
    ~Threat() {;}
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetClip();
    void SetToaDo(const int &x,const int &y)
    {
        x_pos_=x;
        y_pos_=y;
    }

    void dichuyen(Map& map_data,GameMap &game_map,SDL_Rect bomb);
    void sethuongdi(int x)
    {
        huongdi=x;
    }
    void deletetile()
    {
        rect_.x=0;
        rect_.y=0;
        rect_.w=0;
        rect_.h=0;
    }
    bool getdichuyen()
    {
        return is_dichuyen;
    }
    void setdichuyen(bool t)
    {
        is_dichuyen=t;
    }
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int Threat_width;
    int Threat_height;

    int frame_;

    SDL_Rect clip_[4];

    int huongdi;
    bool is_dichuyen;
};
#endif // THREAT_H_

