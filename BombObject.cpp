#include "BombObject.h"


BombObject::BombObject()
{
    bomb_width=0;
    bomb_height=0;
    frame_=0;
    bom_no=false;
    logicx  = 0;
    logicy = 0;
//  time_bom_no=0;
}
BombObject::~BombObject()
{

}
void BombObject::SetClip()
{
    clip_[0].x=0;
    clip_[0].y=0;
    clip_[0].w=63;
    clip_[0].h=70;

    clip_[1].x=63;
    clip_[1].y=0;
    clip_[1].w=64;
    clip_[1].h=65;

    clip_[2].x=127;
    clip_[2].y=0;
    clip_[2].w=64;
    clip_[2].h=65;

    clip_[3].x=191;
    clip_[3].y=0;
    clip_[3].w=64;
    clip_[3].h=65;

    clip_[4].x=255;
    clip_[4].y=0;
    clip_[4].w=63;
    clip_[4].h=65;

}
bool BombObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path,screen);
    {
        bomb_width=rect_.w/5;
        bomb_height=rect_.h;
        rect_.w /= 5;
    }
    return ret;
}
void BombObject::Show(SDL_Renderer* screen)
{
    frame_++;

    if(frame_>=5)
    {
        frame_=0;
    }

    SDL_Rect *current_clip=&clip_[frame_];

    bomb_width=clip_[frame_].w;
    bomb_height=clip_[frame_].h;
    logicx = rect_.x;
    logicy = rect_.y;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BombObject::SetClipBom()
{
    clip_bom_no[0].x=0;
    clip_bom_no[0].y=0;
    clip_bom_no[0].w=70;
    clip_bom_no[0].h=70;

    clip_bom_no[1].x=70;
    clip_bom_no[1].y=0;
    clip_bom_no[1].w=70;
    clip_bom_no[1].h=70;

    clip_bom_no[2].x=70*2;
    clip_bom_no[2].y=0;
    clip_bom_no[2].w=70;
    clip_bom_no[2].h=70;

    clip_bom_no[3].x=70*3;
    clip_bom_no[3].y=0;
    clip_bom_no[3].w=70;
    clip_bom_no[3].h=70;

    clip_bom_no[4].x=70*4;
    clip_bom_no[4].y=0;
    clip_bom_no[4].w=70;
    clip_bom_no[4].h=70;

}
void BombObject::ShowBomNoMiddle(SDL_Renderer* screen,Map &map_data_)
{
    frame_++;
    if(frame_>=5)
    {
        frame_=0;
    }
    SDL_Rect *current_clip=&clip_bom_no[frame_];

    bomb_width=clip_bom_no[frame_].w;
    bomb_height=clip_bom_no[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BombObject::ShowBomNoDown(SDL_Renderer* screen,Map &map_data_)
{
    if(frame_>=5)
    {
        frame_=0;
    }
    SDL_Rect *current_clip=&clip_bom_no[frame_];

    bomb_width=clip_bom_no[frame_].w;
    bomb_height=clip_bom_no[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y-map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
    // sleep(10);
}
void BombObject::ShowBomNoUp(SDL_Renderer* screen,Map &map_data_)
{
    if(frame_>=5)
    {

        frame_=0;
    }
    SDL_Rect *current_clip=&clip_bom_no[frame_];

    bomb_width=clip_bom_no[frame_].w;
    bomb_height=clip_bom_no[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BombObject::ShowBomNoLeft(SDL_Renderer* screen,Map &map_data_)
{
    if(frame_>=5)
    {
        frame_=0;
    }
    SDL_Rect *current_clip=&clip_bom_no[frame_];

    bomb_width=clip_bom_no[frame_].w+2;
    bomb_height=clip_bom_no[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BombObject::ShowBomNoRight(SDL_Renderer* screen,Map &map_data_)
{
    if(frame_>=5)
    {

        frame_=0;
    }
    SDL_Rect *current_clip=&clip_bom_no[frame_];

    bomb_width=clip_bom_no[frame_].w-2;
    bomb_height=clip_bom_no[frame_].h;
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,bomb_width,bomb_height};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);

}
void BombObject::logicbomno(Map& map_data,GameMap& game_map)
{
    int x = logicx;
    int y = logicy;

    x=(x+33)/70;
    y=(y+33)/70;
    //std::cout<<x<<" "<<y<<"\n";
    Tile_Threat* p_tile_threat=game_map.gettile();
    for(int i=0; i<5; i++)
    {
        int x1=x+dx[i];
        int y1=y+dy[i];
        if(x1>=0&&y1>=0&&x1<MAP_X&&y1<MAP_Y)
        {

            for(int j=0; j<100; j++)
            {
                SDL_Rect tmp=p_tile_threat[j].GetRectmThreat();
                if(tmp.x/70==x1&&tmp.y/70==y1)
                {
                    if(CHECK == true && (rand()%99) == j){
                        map_data.tile[y1][x1] = 9; CHECK =false;
                    }
                    else if(map_data.tile[y1][x1] == 2)
                    {
                        map_data.tile[y1][x1]=0;
                        p_tile_threat[j].deletetile();
                    }
                }
            }
        }
    }
}
