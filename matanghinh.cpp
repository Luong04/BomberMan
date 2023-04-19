
#include "matanghinh.h"

Matanghinh::Matanghinh()
{
    is_dichuyen = true;
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 2;
    y_val_ = 2;
    Matanghinh_width = 0;
    Matanghinh_height = 0;
    huongdi = 0;
}

void Matanghinh::SetClip()
{
    for(int i = 0; i < 30;i++)
    {
        clip_[i].x=63*i;
        clip_[i].y=0;
        clip_[i].w=63;
        clip_[i].h=68;
    }
}

bool Matanghinh::loadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret)
    {
        Matanghinh_width=this->rect_.w/30;
        Matanghinh_height=this->rect_.h;
        rect_.w /= 30;
    }
    return ret;
}

void Matanghinh::Show(SDL_Renderer* screen)
{
    frame_++;

    if(frame_>=30)
    {
        frame_=0;
    }

    SDL_Rect *current_clip=&clip_[frame_];

    Matanghinh_width=clip_[frame_].w;
    Matanghinh_height=clip_[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,Matanghinh_width,Matanghinh_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
}

void Matanghinh::dichuyen()
{
    if(huongdi == 1)
    {
        x_pos_ += x_val_;
        if(x_pos_<= 70 || x_pos_ >=2240)
        {
            x_val_ = -x_val_;
        }
    }
    else if(huongdi == 2)
    {
        y_pos_ += y_val_;
        if(y_pos_ <= 140 || y_pos_ >= 1120)
        {
            y_val_ = -y_val_;
        }
    }
    rect_.x = x_pos_;
    rect_.y = y_pos_;
}


