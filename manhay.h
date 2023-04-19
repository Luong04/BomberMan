#ifndef MANHAY _H_
#define MANHAY_H_
#include "CommonFunc.h"
#include "map.h"
#include "BaseObject.h"
class Manhay : public BaseObject
{
public:
    Manhay();
    ~Manhay(){;}
    void SetClip();
    bool loadImg(std::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer * screen);
    void dichuyen(Map& map_data, GameMap &game_map,SDL_Rect bomb);
    void SetToaDo(const int &x,const int &y)
    {
        x_pos_ = x;
        y_pos_ = y;
    }
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

    int Manhay_width;
    int Manhay_height;

    int frame_;
    SDL_Rect clip_[8];
    int huongdi;
    bool is_dichuyen;
};
#endif // MANHAY_H_
