
#include "ghostAI.h"

Ghost::Ghost()
{
    frame_=0;
    srand(time(0));
    x_pos_=1800+rand()%500;
    y_pos_=1400+rand()%350;
    y_val_=0;
    x_val_=0;
    Ghost_width=0;
    Ghost_height=0;
    da_chet=0;
    load_y = 0;
}

bool Ghost::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret)
    {
        Ghost_width=this->rect_.w/5;
        Ghost_height=this->rect_.h/2;
    }
    return ret;
}
void Ghost::Show(SDL_Renderer* screen)
{
    if(this -> x_val_ <= 0)
    {
        setload_y(1);
    }
    else
    {
        setload_y(2);
    }
    frame_++;

    if(frame_>=5)
    {
        frame_=0;
    }

    SDL_Rect *current_clip=&clip_[getload_y()-1][frame_];
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,Ghost_width,Ghost_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
}

void Ghost::SetClip()
{
    for(int i = 0; i < 2; i++){
    clip_[i][0].x=0;
    clip_[i][0].y=67*i;
    clip_[i][0].w=59;
    clip_[i][0].h=67;

    clip_[i][1].x=59;
    clip_[i][1].y=67*i;
    clip_[i][1].w=69;
    clip_[i][1].h=67;

    clip_[i][2].x=118;
    clip_[i][2].y=67*i;
    clip_[i][2].w=59;
    clip_[i][2].h=67;

    clip_[i][3].x=177;
    clip_[i][3].y=67*i;
    clip_[i][3].w=59;
    clip_[i][3].h=67;

    clip_[i][4].x=236;
    clip_[i][4].y=67*i;
    clip_[i][4].w=59;
    clip_[i][4].h=67;
}
}
void Ghost::dichuyen(MainObject &main_, Mix_Chunk* ghost, bool mute_)
{

    x_pos_+=x_val_;
    rect_.x=x_pos_;

    if( this->x_pos_ > main_.posx())
        x_val_ = -3;
    else if(this->x_pos_<main_.posx())
        x_val_ = 3;
    else x_val_ = 0;

    y_pos_ += y_val_;
    rect_.y = y_pos_;

    if( this->y_pos_ > main_.posy())
        y_val_ = -3;
    else if(this->x_pos_<main_.posy())
        y_val_ = 3;
    else y_val_ = 0;

    if((abs(x_pos_ - map_x_) <= SCREEN_WIDTH && (x_pos_ - map_x_)>=SCREEN_WIDTH/2) && (abs(y_pos_ - map_y_) <= SCREEN_HEIGHT ))
    {
        if(mute_ == false)
            {
                Mix_PlayChannel(-1,ghost,0);
            }
        else
            {
               Mix_HaltChannel(-1);
            }
    }
}


