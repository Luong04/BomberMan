
#include "MainObject.h"

MainObject::MainObject()
{
    frame_=0;
    x_pos_=70;
    y_pos_=140;
    y_val_=0;
    x_val_=0;
    y_loadanh = 0;
    status_=-1;
    input_type.left=0;
    input_type.right=0;
    input_type.down=0;
    input_type.up=0;
    dat_bom=false;
    set_x_bom=0;
    set_y_bom=0;
    toc_do=0;
    time_bom_no=0;
    map_x_ = 0;
    map_y_ = 0;
    checkkey = 0;
}
bool MainObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    return BaseObject::LoadImg(path,screen);

}
void MainObject::Show(SDL_Renderer* screen)
{
    if(status_==1)
    {
        sety_loadanh(0) ;
    }
    else if(status_==2)
    {
        sety_loadanh(DOT_HEIGHT);
    }
    else if(status_==3)
    {
        sety_loadanh(DOT_HEIGHT * 2);
    }
    else if(status_==4)
    {
        sety_loadanh(DOT_HEIGHT * 3);
    }

    if(input_type.left==1||input_type.right==1||input_type.up==1||input_type.down==1)
    {
        frame_++;
    }
    else
    {
        frame_=0;
    }
    if(frame_>=5)
    {
        frame_=0;
    }

    SDL_Rect *current_clip=&clip_[status_-1][frame_];
    SDL_Rect renderquad= {rect_.x - map_x_,rect_.y - map_y_,DOT_WIDTH,DOT_HEIGHT};
    SDL_RenderCopy(screen,p_object_,current_clip,&renderquad);
}
void MainObject::handle(SDL_Event &e,SDL_Renderer* screen)
{
    if(e.type==SDL_KEYDOWN &&e.key.repeat==0)
    {
        setcheckkey(1);
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            status_=3;
            input_type.up=1;
            input_type.down=0;
            input_type.left=0;
            input_type.right=0;
            y_val_-=toc_do;
            break;
        case SDLK_s:
            status_=4;
            input_type.up=0;
            input_type.down=1;
            input_type.left=0;
            input_type.right=0;
            y_val_+=toc_do;
            break;
        case SDLK_a:
            status_=2;
            input_type.up=0;
            input_type.down=0;
            input_type.left=1;
            input_type.right=0;
            x_val_-=toc_do;
            break;
        case SDLK_d:
            status_=1;
            input_type.up=0;
            input_type.down=0;
            input_type.left=0;
            input_type.right=1;
            x_val_+=toc_do;
            break;
        case SDLK_SPACE:
            dat_bom=true;
            bomb.SetBomno(false);
            set_x_bom=x_pos_;
            set_y_bom=y_pos_;
            break;

        }
    }
    else if (getcheckkey()==1 && e.type==SDL_KEYUP && e.key.repeat==0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            status_=3;
            input_type.up=0;
            input_type.down=0;
            input_type.left=0;
            input_type.right=0;
            y_val_+=toc_do;
            break;
        case SDLK_s:
            status_=4;
            input_type.up=0;
            input_type.down=0;
            input_type.left=0;
            input_type.right=0;
            y_val_-=toc_do;
            break;
        case SDLK_a:
            status_=2;
            input_type.up=0;
            input_type.down=0;
            input_type.left=0;
            input_type.right=0;
            x_val_+=toc_do;
            break;
        case SDLK_d:
            status_=1;
            input_type.up=0;
            input_type.down=0;
            input_type.left=0;
            input_type.right=0;
            x_val_-=toc_do;
            break;
        case SDLK_SPACE:
            dat_bom=true;
            bomb.SetBomno(false);
            break;

        }
    }
}


void MainObject::SetClip()
{
    for(int i = 0; i < 4; i++)
    {
        clip_[i][0].x=0;
        clip_[i][0].y= i*DOT_HEIGHT;
        clip_[i][0].w=DOT_WIDTH;
        clip_[i][0].h=DOT_HEIGHT;

        clip_[i][1].x=DOT_WIDTH;
        clip_[i][1].y=i*DOT_HEIGHT;
        clip_[i][1].w=DOT_WIDTH;
        clip_[i][1].h=DOT_HEIGHT;

        clip_[i][2].x=2*DOT_WIDTH;
        clip_[i][2].y=i*DOT_HEIGHT;
        clip_[i][2].w=DOT_WIDTH;
        clip_[i][2].h=DOT_HEIGHT;

        clip_[i][3].x=3*DOT_WIDTH;
        clip_[i][3].y=i*DOT_HEIGHT;
        clip_[i][3].w=DOT_HEIGHT;
        clip_[i][3].h=DOT_HEIGHT;

        clip_[i][4].x=4*DOT_WIDTH;
        clip_[i][4].y=i*DOT_HEIGHT;
        clip_[i][4].w=DOT_WIDTH;
        clip_[i][4].h=DOT_HEIGHT;

    }
}

void MainObject::dichuyen(Map& map_data,GameMap &game_map)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    x1 = (x_pos_+ x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ +DOT_WIDTH -1)/TILE_SIZE;
    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + DOT_HEIGHT -1)/TILE_SIZE;

    if(x1>=1 && x2< MAP_X-1 && y1 >= 2 && y2 < MAP_Y-1)
    {
        if(x_val_>0)
        {
            if(map_data.tile[y1][x2] ==1 || map_data.tile[y1][x2] ==2 || map_data.tile[y2][x2] == 1 || map_data.tile[y2][x2] ==2 )
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= DOT_WIDTH + 1;
                x_pos_ -= x_val_;
            }
        }
        else if( x_val_ < 0)
        {
            if( map_data.tile[y1][x1] == 1 || map_data.tile[y1][x1] == 2|| map_data.tile[y2][x1] == 1 || map_data.tile[y1][x2] == 2)
            {
                x_pos_ = (x1 + 1)* TILE_SIZE;
                x_pos_ -= x_val_;
            }
        }
    }
    else if(x1<1 && y1>= 2 && y2 < MAP_Y - 1)
    {
        x_pos_ = (x1 + 1)* TILE_SIZE;
        x_pos_ -= x_val_;
    }
    else if(x2 >= MAP_X - 1 && y1>= 2 && y2 < MAP_Y - 1)
    {
        x_pos_ = (x2 - 1)* TILE_SIZE;
        x_pos_ -= x_val_;
    }

    rect_.x = x_pos_;

    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + DOT_WIDTH)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + DOT_HEIGHT - 1)/TILE_SIZE;

    if(x1 >= 1 && x2 < MAP_X-1 &&y1 >=2 &&y2 <MAP_Y-1)
    {
        if(y_val_>0)
        {
            if(map_data.tile[y2][x1] ==1 || map_data.tile[y2][x1] ==2 || map_data.tile[y2][x2] == 1 || map_data.tile[y2][x2] == 2)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= DOT_HEIGHT + 1;
                y_pos_ -= y_val_ ;
            }
        }
        else if( y_val_ < 0)
        {
            if( map_data.tile[y1][x1] == 1 || map_data.tile[y1][x1] == 2|| map_data.tile[y1][x2] == 1 || map_data.tile[y1][x2] ==2)
            {
                y_pos_ = (y1 + 1)* TILE_SIZE;
                y_pos_ -= y_val_;
            }
        }
    }
    else if(x1>=1 && y1< 2 && x2 < MAP_X - 1)
    {
        y_pos_ = (y1 + 1)* TILE_SIZE;
        y_pos_ -= y_val_;
    }
    else if(y2 >= MAP_Y - 1 && x1>= 1 && x2 < MAP_X - 1)
    {
        y_pos_ = (y2 - 1)* TILE_SIZE;
        y_pos_ -= y_val_;
    }
    rect_.y = y_pos_;

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    CenterOnMap(map_data);

}


void MainObject::DatBom(SDL_Renderer* screen, Map &map_data_,Mix_Chunk* bom, bool mute_)
{
    bomb.LoadImg("loadimg/bom_chuoi.png",screen);

    bomb.SetClip();
    if(vitrino == 0)
    {
        int x=set_x_bom;
        int y=set_y_bom;
        bomb.SetRect(x,y);
    }

    time_bom_no++;
    bomb.SetXY(map_data_.start_x_,map_data_.start_y_);
    bomb.Show(screen);
    if(mute_ == false) Mix_PlayChannel(-1,bom,0);
    else Mix_HaltChannel(-1);
}

void MainObject::Bom_no(SDL_Renderer* screen, Map &map_data_)
{
    bomb.LoadImg("loadimg/actors1.png",screen);
    bomb.SetClipBom();
    int x,y;
    if(vitrino == 0)
    {
        x=set_x_bom;
        y=set_y_bom;
        bomb.SetRect(x,y);
    }
    bomb.SetXY(map_data_.start_x_,map_data_.start_y_);
    bomb.ShowBomNoMiddle(screen,map_data_);

    bomb.LoadImg("loadimg/bom_down.png",screen);
    int x1=x;
    int y1=y+70;
    bomb.SetRect(x1,y1);
    bomb.ShowBomNoDown(screen,map_data_);

    bomb.LoadImg("loadimg/bom_up.png",screen);
    int x2=x;
    int y2=y-70;
    bomb.SetRect(x2,y2);
    bomb.ShowBomNoUp(screen,map_data_);

    bomb.LoadImg("loadimg/bom_right.png",screen);
    int x4=x+70;
    int y4=y;
    bomb.SetRect(x4,y4);
    bomb.ShowBomNoRight(screen,map_data_);

    bomb.LoadImg("loadimg/bom_left.png",screen);
    int x3=x-70;
    int y3=y;
    bomb.SetRect(x3,y3);
    bomb.ShowBomNoLeft(screen,map_data_);

//    bomb.SetRect(x,y);
}

void MainObject::CenterOnMap(Map &map_data)
{
    map_data.start_x_ =  x_pos_ - SCREEN_WIDTH / 2;
    //Keep the camera in bounds
    if( map_data.start_x_ < 0 )
    {
        map_data.start_x_ = 0;
    }
    else if( map_data.start_x_ + SCREEN_WIDTH > LEVEL_WIDTH )
    {
        map_data.start_x_ = LEVEL_WIDTH - SCREEN_WIDTH;
    }
    map_data.start_y_ =  y_pos_  - SCREEN_HEIGHT / 2;
    if( map_data.start_y_ < 0 )
    {
        map_data.start_y_ = 0;
    }
    else if( map_data.start_y_ +SCREEN_HEIGHT > LEVEL_HEIGHT )
    {
        map_data.start_y_ = LEVEL_HEIGHT - SCREEN_HEIGHT;
    }
}
