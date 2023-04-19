#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"
class BaseObject
{
public:
    //Initializes variables
    BaseObject();

    //Deallocates memory
    ~BaseObject();
    void SetRect(const int &x,const int &y)
    {
        rect_.x=x;
        rect_.y=y;
    }
    void Setw_h(const int &w, const int &h){
        rect_.w = w;
        rect_.h = h;
    }
    SDL_Rect GetRect()
    {
        return rect_;
    }
    SDL_Texture* GetObject()
    {
        return p_object_;
    }
    virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Render(SDL_Renderer* des);
    void SetXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
    void free();
    int toa_do_x()
    {
        return rect_.x;
    }
    int toa_do_y()
    {
        return rect_.y;
    }
    int do_dai_w()
    {
        return rect_.w;
    }
    int do_dai_h()
    {
        return rect_.h;
    }
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
    int map_x_;
    int map_y_;
};
#endif // BASE_OBJECT_H_
