#ifndef MATANGHINH_H_
#define MATANGHINH_H_
#include "BaseObject.h"
#include "CommonFunc.h"
#include "map.h"

class Matanghinh : public BaseObject
{
public:
    Matanghinh();
    ~Matanghinh(){;}
    void SetClip();
    bool loadImg(std::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer * screen);
    void dichuyen();
    void SetToaDo(const int &x,const int &y)
    {
        x_pos_ = x;
        y_pos_ = y;
    }
    float getx(){return x_pos_;}
    float gety(){return y_pos_;}
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

    int Matanghinh_width;
    int Matanghinh_height;

    int frame_;
    SDL_Rect clip_[37];
    int huongdi;
    bool is_dichuyen;
};


#endif // MATANGHINH_H_
