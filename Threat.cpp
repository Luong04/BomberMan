
#include "Threat.h"

Threat::Threat()
{
    is_dichuyen=true;
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    y_val_=3;
    x_val_=3;
    Threat_width=0;
    Threat_height=0;
    huongdi=0;
}

bool Threat::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    if(ret)
    {
        Threat_width=this->rect_.w/4;
        Threat_height=this->rect_.h;
        rect_.w /= 4;
    }
    return ret;
}
void Threat::Show(SDL_Renderer* screen)
{
    frame_++;

    if(frame_>=4)
    {
        frame_=0;
    }

    SDL_Rect *current_clip=&clip_[frame_];

    Threat_width=clip_[frame_].w;
    Threat_height=clip_[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,Threat_width,Threat_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
}

void Threat::SetClip()
{
    clip_[0].x=0;
    clip_[0].y=0;
    clip_[0].w=65;
    clip_[0].h=65;

    clip_[1].x=65;
    clip_[1].y=0;
    clip_[1].w=65;
    clip_[1].h=65;

    clip_[2].x=130;
    clip_[2].y=0;
    clip_[2].w=65;
    clip_[2].h=65;

    clip_[3].x=195;
    clip_[3].y=0;
    clip_[3].w=65;
    clip_[3].h=65;

}
void Threat::dichuyen(Map& map_data,GameMap &game_map,SDL_Rect bomb)
{
    int THREAT_WIDTH=this->rect_.w;
    int THREAT_HEIGHT=this->rect_.h;
    Tile_Threat*tile= game_map.gettile();
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    x1 = x_pos_/TILE_SIZE;
    x2 = (x_pos_ + THREAT_WIDTH )/TILE_SIZE;
    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + THREAT_HEIGHT )/TILE_SIZE;

    if(huongdi==1)
    {
        int x1 = 0;
        int x2 = 0;
        int y1 = 0;
        int y2 = 0;

        x1 = (x_pos_+ x_val_)/TILE_SIZE;
        x2 = (x_pos_ + x_val_ +THREAT_WIDTH -1)/TILE_SIZE;
        y1 = (y_pos_)/TILE_SIZE;
        y2 = (y_pos_ + THREAT_HEIGHT -1)/TILE_SIZE;

        if(x1>=1 && x2< MAP_X-1 && y1 >= 2 && y2 < MAP_Y-1)
        {
            if(x_val_>0)
            {
                if(map_data.tile[y1][x2] ==1 || map_data.tile[y1][x2] ==2 || map_data.tile[y2][x2] == 1 || map_data.tile[y2][x2] ==2 )
                {
                    x_pos_ = x2 * TILE_SIZE;
                    x_pos_ -= THREAT_WIDTH + 1;
                    x_val_ = -x_val_;
                }
            }
            else if( x_val_ < 0)
            {
                if( map_data.tile[y1][x1] == 1 || map_data.tile[y1][x1] == 2|| map_data.tile[y2][x1] == 1 || map_data.tile[y1][x2] == 2)
                {
                    x_pos_ = (x1 + 1)* TILE_SIZE;
                    x_val_ =- x_val_;
                }
            }
        }
        else if(x1<1 && y1>= 2 && y2 < MAP_Y - 1)
        {
            x_pos_ = (x1 + 1)* TILE_SIZE;
            x_val_ = -x_val_;
        }
        else if(x2 >= MAP_X - 1 && y1>= 2 && y2 < MAP_Y - 1)
        {
            x_pos_ = (x2 - 1)* TILE_SIZE;
            x_val_ = -x_val_;
        }

        SDL_Rect threat_o = this->GetRect();

        bool t=SDLCommonFunc::CheckCollision1(bomb,threat_o);
        if(t)
        {
            x_val_=-x_val_;
        }
         x_pos_ += x_val_;
         rect_.x = x_pos_;
         rect_.y = y_pos_;
    }

    else if(huongdi==2)
    {
        int x1 = 0;
        int x2 = 0;
        int y1 = 0;
        int y2 = 0;
        x1 = (x_pos_)/TILE_SIZE;
        x2 = (x_pos_ + THREAT_WIDTH)/TILE_SIZE;

        y1 = (y_pos_ + y_val_)/TILE_SIZE;
        y2 = (y_pos_ + y_val_ + THREAT_HEIGHT - 1)/TILE_SIZE;

        if(x1 >= 1 && x2 < MAP_X-1 &&y1 >=2 &&y2 <MAP_Y-1)
        {
            if(y_val_>0)
            {
                if(map_data.tile[y2][x1] ==1 || map_data.tile[y2][x1] ==2 || map_data.tile[y2][x2] == 1 || map_data.tile[y2][x2] == 2)
                {
                    y_pos_ = y2 * TILE_SIZE;
                    y_pos_ -= THREAT_HEIGHT + 1;
                    y_val_ = -y_val_ ;
                }
            }
            else if( y_val_ < 0)
            {
                if( map_data.tile[y1][x1] == 1 || map_data.tile[y1][x1] == 2|| map_data.tile[y1][x2] == 1 || map_data.tile[y1][x2] ==2)
                {
                    y_pos_ = (y1 + 1)* TILE_SIZE;
                    y_val_ = -y_val_;
                }
            }
        }
        else if(x1>=1 && y1< 2 && x2 < MAP_X - 1)
        {
            y_pos_ = (y1 + 1)* TILE_SIZE;
            y_val_= -y_val_;
        }
        else if(y2 >= MAP_Y - 1 && x1>= 1 && x2 < MAP_X - 1)
        {
            y_pos_ = (y2 - 1)* TILE_SIZE;
            y_val_ = -y_val_;
        }

        SDL_Rect threat_o = this->GetRect();

        bool t=SDLCommonFunc::CheckCollision1(bomb,threat_o);
        if(t)
        {
            y_val_=-y_val_;
        }
        y_pos_ += y_val_;
        rect_.y = y_pos_;
        rect_.x=x_pos_;
    }
}

