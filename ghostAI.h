
#ifndef GHOSTAI_H_
#define GHOSTAI_H_
#include "CommonFunc.h"
#include "map.h"
#include "BaseObject.h"
#include "MainObject.h"
class Ghost:public BaseObject
{
public:
    Ghost();
    ~Ghost() {;}
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetClip();
    void SetToaDo(const int &x,const int &y)
    {
        x_pos_=x;
        y_pos_=y;
    }
    void dichuyen(MainObject &main_,Mix_Chunk* ghost);
    void setda_chet(int x)
    {
        da_chet = x;
    }
    int getda_chet()
    {
        return da_chet;
    }
    void setload_y(int k){
        load_y = k;
    }
    int getload_y(){
        return load_y;
    }
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int Ghost_width;
    int Ghost_height;

    int frame_;

    SDL_Rect clip_[2][5];

    int da_chet;
    int load_y;
};
#endif // GHOSTAI_H_


