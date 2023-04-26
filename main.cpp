#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "map.h"
#include "BombObject.h"
#include "Threat.h"
#include "ghostAI.h"
#include "Power.h"
#include "TextObject.h"
#include "manhay.h"
#include "matanghinh.h"

using namespace std;

SDL_Window* gWindow=NULL;
SDL_Renderer* gScreen=NULL;
SDL_Texture* gText=NULL;

BaseObject gBackground;
BaseObject g_img_menu;
BaseObject g_help;
BaseObject g_pause;
BaseObject g_mute;
BaseObject g_gameover;
BaseObject g_victory;
BaseObject g_victory2;

TTF_Font *font_ = NULL;
Threat gThreat[25];
Manhay gManhay[7];
Matanghinh gMatanghinh[5];

GameMap bricks;
BaseObject win;
BaseObject gLine;
Power player_power;

Mix_Chunk* g_sound_bkgr = NULL;
Mix_Chunk* ghost_sound = NULL;
Mix_Chunk* bom_sound = NULL;
Mix_Chunk* start_sound = NULL;
Mix_Chunk* g_end_sound = NULL;
Mix_Chunk* g_win_sound = NULL;
Mix_Chunk* g_win2_sound = NULL;
void init()
{
    SDL_INIT_EVERYTHING;
    gWindow=SDL_CreateWindow("BOMBER MAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    gScreen=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    TTF_Init();
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    //int Mix_AllocateChannels(3);
    g_sound_bkgr = Mix_LoadWAV("loadsound/nhacnen.wav");
    ghost_sound = Mix_LoadWAV("loadsound/ghost1loc.wav");
    bom_sound = Mix_LoadWAV("loadsound/boom.wav");
    start_sound = Mix_LoadWAV("loadsound/bkgrsound.wav");
    g_end_sound = Mix_LoadWAV("loadsound/gameover.wav");
    g_win_sound = Mix_LoadWAV("loadsound/traothuong.wav");
    g_win2_sound = Mix_LoadWAV("loadsound/victory.wav");
}

void loadmedia()
{
    gBackground.LoadImg("loadimg/bkgr.png",gScreen);
    g_img_menu.LoadImg("loadimg/menu.png",gScreen);
    g_help.LoadImg("loadimg/help.png",gScreen);
    gLine.LoadImg("loadimg/line2.png",gScreen);
    g_pause.LoadImg("loadimg/pause.png",gScreen);
    g_mute.LoadImg("loadimg/mute.png",gScreen);
    g_gameover.LoadImg("loadimg/gameover.png",gScreen);
    g_victory.LoadImg("loadimg/victory.png",gScreen);
    g_victory2.LoadImg("loadimg.victory2.png",gScreen);
    for(int i=0; i<25; i++)
    {
        gThreat[i].LoadImg("loadimg/threat.png",gScreen);
        gThreat[i].SetClip();
    }
    for(int i = 0; i < 7; i++)
    {
        gManhay[i].loadImg("loadimg/manhay.png",gScreen);
        gManhay[i].SetClip();
    }
    for(int i = 0 ; i < 5; i++)
    {
        gMatanghinh[i].loadImg("loadimg/matanghinh2.png",gScreen);
        gMatanghinh[i].SetClip();
    }
    bricks.LoadMap("map1.txt");
    bricks.LoadTiles(gScreen);
    win.LoadImg("loadimg/qua_man.png", gScreen);
    player_power.LoadImg("loadimg/lives.png",gScreen);
    font_ = TTF_OpenFont("font/ALGER.TTF",30);
}

void close()
{
    SDL_DestroyRenderer(gScreen);
    gScreen=NULL;
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    SDL_DestroyTexture(gText);
    gText=NULL;
    Mix_FreeChunk(g_sound_bkgr);
    Mix_FreeChunk(ghost_sound);
    Mix_FreeChunk(bom_sound);
    Mix_FreeChunk(start_sound);
    Mix_FreeChunk(g_end_sound);

    SDL_Quit();
    Mix_Quit();
}

int ShowMenu(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* startsound)
{
    const int kMenuItemNum = 3;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 557;
    pos_arr[0].y = 375;
    pos_arr[0].w = 200;
    pos_arr[0].h = 64;

    pos_arr[1].x = 558;
    pos_arr[1].y = 470;
    pos_arr[1].w = 200;
    pos_arr[1].h = 64;

    pos_arr[2].x = 558;
    pos_arr[2].y = 560;
    pos_arr[2].w = 200;
    pos_arr[2].h = 64;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
    text_menu[0].Setw_h(pos_arr[0].w, pos_arr[0].h);

    text_menu[1].SetText("Help");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);
    text_menu[1].Setw_h(pos_arr[1].w, pos_arr[1].h);

    text_menu[2].SetText("Exit");
    text_menu[2].SetColor(TextObject::WHITE_TEXT);
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);
    text_menu[2].Setw_h(pos_arr[2].w, pos_arr[2].h);

    bool selected[kMenuItemNum] = {0,0,0};
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while(true)
    {
        Mix_PlayChannel(-1,startsound,-1);
        g_img_menu.Render(screen);
        for(int i = 0 ; i < kMenuItemNum; i++)
        {
            text_menu[i].LoadFromRenderText(font, screen);
            text_menu[i].RenderText(screen,pos_arr[i].x,pos_arr[i].y);
        }

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 3;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for( int i = 0 ; i < kMenuItemNum; i++)
                {
                    if(SDLCommonFunc::CheckFocusWithRect(xm + 50,ym + 10,text_menu[i].GetRect()))
                    {
                        if(selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if(selected[i]==true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;

                for( int i = 0; i < kMenuItemNum; i++)
                {
                    if(SDLCommonFunc::CheckFocusWithRect(xm + 50,ym + 10, text_menu[i].GetRect()))
                        return i+1;
                }
            }
            break;
            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE)
                    return 3;
            default:
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
    return 0;
}

int pause(SDL_Renderer *screen)
{
    int numfunc = 3;
    SDL_Rect pos_arr[numfunc];
    pos_arr[0].x = 420;
    pos_arr[0].y = 325;
    pos_arr[0].w = 110;
    pos_arr[0].h = 125;

    pos_arr[1].x = 560;
    pos_arr[1].y = 325;
    pos_arr[1].w = 110;
    pos_arr[1].h = 125;

    pos_arr[2].x = 700;
    pos_arr[2].y = 325;
    pos_arr[2].w = 110;
    pos_arr[2].h = 125;

    bool selected[numfunc] = {0,0,mute};
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while(true)
    {
        g_pause.SetRect(365,285);
        g_pause.Render(screen);

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                xm = m_event.button.x;
                ym = m_event.button.y;

                for( int i = 0; i < 2; i++)
                {
                    if(SDLCommonFunc::CheckFocusWithRect(xm,ym, pos_arr[i]))
                        return i+1;
                }
                if(SDLCommonFunc::CheckFocusWithRect(xm,ym,pos_arr[2]))
                {
                    if(selected[2] == true) selected[2] = false;
                    else selected[2] = true;
                }
            default:
                break;
            }
        }

        if(selected[2] == true)
        {
            Mix_Pause(-1);
            g_mute.SetRect(682,325);
            g_mute.Render(screen);
        }

        else
        {
            if(Mix_Paused)
            {
                Mix_Resume(-1);
            }
        }
        mute = selected[2];
        SDL_RenderPresent(screen);
    }

    return 3;
}

bool gameover(SDL_Renderer * screen, Mix_Chunk *gameover_)
{
    SDL_Event e;
    while(true)
    {
        g_gameover.SetRect(145,235);
        g_gameover.Render(screen);
        if(mute == false)Mix_PlayChannel(-1,gameover_,0);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) return 1;
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            }
        }
        SDL_RenderPresent(screen);
    }
    return 0;
}
bool victory(SDL_Renderer *screen, Mix_Chunk *victory_sound, int victory_image)
{
    SDL_Event e;
    while(true)
    {
        if(victory_image == 1)
        {
            g_victory.SetRect(272,85);
            g_victory.Render(screen);
        }
        else if(victory_image == 2)
        {
            g_victory2.SetRect(288,85);
            g_victory2.Render(screen);
        }
        if(mute == false)Mix_PlayChannel(-1,victory_sound,0);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) return 1;
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
            }
        }
        SDL_RenderPresent(screen);
    }
    return 0;
}
int main(int argc,char* args[])
{
label:
    init();
    loadmedia();

    int menu = 0;
    int time_before = 0;
    while(menu == 0)
    {
        menu = ShowMenu(gScreen,font_,start_sound);
        Uint32 time_b = SDL_GetTicks()/1000;
        if(menu == 1)
        {
            time_before = time_b;
            Mix_HaltChannel(-1);
        }
        else if(menu == 2)
        {
            SDL_Event mouse_help;
            int xm;
            int ym;
            SDL_Rect daunhan;
            daunhan.x = 932;
            daunhan.y = 80;
            daunhan.w = 70;
            daunhan.h = 76;
            while(menu == 2)
            {
                g_help.SetRect(192,80);
                g_help.Render(gScreen);
                while(SDL_PollEvent(&mouse_help))
                {
                    switch (mouse_help.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        xm = mouse_help.button.x;
                        ym = mouse_help.button.y;
                        if(SDLCommonFunc::CheckFocusWithRect(xm,ym,daunhan))
                            menu = 0;
                        break;
                    }
                    default:
                        break;
                    }
                }
                SDL_RenderPresent(gScreen);
            }
        }
        else if(menu == 3)
        {
            Mix_HaltChannel(-1);
            close();
            return 0;
        }
    }


    player_power.Init();
    int die_number = 0;
    int mark_value = 0;

    for(int i=0; i<25; i++)
    {
        if(i%2==0 )
        {
            gThreat[i].sethuongdi(1);
        }
        else
        {
            gThreat[i].sethuongdi(2);
        }
    }
    for(int j=0; j<7; j++)
    {
        if(j%2==0 )
        {
            gManhay[j].sethuongdi(1);
        }
        else
        {
            gManhay[j].sethuongdi(2);
        }
    }

    TextObject time_game;
    time_game.SetColor(TextObject::BLACK_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::BLACK_TEXT);

    TextObject high_score;
    high_score.SetColor(TextObject::BLACK_TEXT);


    int number_of_threats = 25;
    int number_of_manhay = 7;
    int number_of_matanghinh = 5;

    while(die_number <= 2 )
    {
        gThreat[0].SetToaDo(670,140);
        gThreat[1].SetToaDo(210,140);
        gThreat[2].SetToaDo(210,560);
        gThreat[3].SetToaDo(770,140);
        gThreat[4].SetToaDo(490,280);
        gThreat[5].SetToaDo(1190,140);
        gThreat[6].SetToaDo(350,1120);
        gThreat[7].SetToaDo(1190,1330);
        gThreat[8].SetToaDo(910,280);
        gThreat[9].SetToaDo(1050,1120);
        gThreat[10].SetToaDo(1120,420);
        gThreat[11].SetToaDo(350,280);
        gThreat[12].SetToaDo(1190,840);
        gThreat[13].SetToaDo(490,280);
        gThreat[14].SetToaDo(2100,1120);
        gThreat[15].SetToaDo(2030,1050);
        gThreat[16].SetToaDo(1960,980);
        gThreat[17].SetToaDo(1190,1400);
        gThreat[18].SetToaDo(1330,980);
        gThreat[19].SetToaDo(2170,1120);
        gThreat[20].SetToaDo(2170,560);
        gThreat[21].SetToaDo(1330,560);
        gThreat[22].SetToaDo(1050,840);
        gThreat[23].SetToaDo(1330,700);
        gThreat[24].SetToaDo(630,840);

        gManhay[0].SetToaDo(1190,980);
        gManhay[1].SetToaDo(910,1050);
        gManhay[2].SetToaDo(350,420);
        gManhay[3].SetToaDo(630,1470);
        gManhay[4].SetToaDo(1610,840);
        gManhay[5].SetToaDo(1190,140);
        gManhay[6].SetToaDo(350,1260);

        gMatanghinh[0].SetToaDo(900,350);
        gMatanghinh[1].SetToaDo(500,1050);
        gMatanghinh[2].SetToaDo(2000,435);
        gMatanghinh[3].SetToaDo(811,600);
        gMatanghinh[4].SetToaDo(1700,1400);

        for(int j=0; j<5; j++)
        {
            if(j%2==0 )
            {
                gMatanghinh[j].sethuongdi(1);
            }
            else
            {
                gMatanghinh[j].sethuongdi(2);
            }
        }
        if(mute == false)
        {
            Mix_PlayChannel(-1,g_sound_bkgr,-1);
        }
        else Mix_HaltChannel(-1);

        MainObject main_obj;
        main_obj.LoadImg("loadimg/main.png",gScreen);
        main_obj.SetClip();
        main_obj.settocdo(5);

        Ghost ghostAI;
        ghostAI.LoadImg("loadimg/ghostAI.png",gScreen);
        ghostAI.SetClip();
        bool quit=false;
        int pause_type = 0;
        SDL_Event gevent;
        while(!quit)
        {
            while(SDL_PollEvent(&gevent)!=0)
            {
                if(gevent.type==SDL_QUIT)
                {
                    die_number = 3;
                    quit = true;
                }
                main_obj.handle(gevent,gScreen);

                if(gevent.type == SDL_KEYDOWN)
                {
                    if(gevent.key.keysym.sym == SDLK_p)
                    {
                        pause_type = pause(gScreen);
                    }
                }
                if(pause_type == 3) SDL_Delay(2000);
                else if(pause_type == 1)
                {
                    Mix_HaltChannel(-1);
                    close();
                    goto label;
                }

            }

            Uint32 time_val = SDL_GetTicks()/1000;
            Uint32 val_time = 600 - time_val + time_before;

            if(val_time % 30 == 15)
            {
                for(int i = 0 ; i < 5 ; i++)
                {
                    gMatanghinh[i].sethuongdi((i+val_time) % 2);
                }
            }
            Map map_data = bricks.getMap();
            //show player power

            main_obj.SetXY(map_data.start_x_,map_data.start_y_);
            main_obj.dichuyen(map_data,bricks);

            gBackground.Render(gScreen);
            main_obj.Show(gScreen);
            bricks.DrawMap(gScreen,win, map_data);
            gLine.Render(gScreen);

            if(main_obj.getdatbom())
            {
                main_obj.DatBom(gScreen, map_data,bom_sound, mute);

                if(main_obj.time_bom_no_()>0) main_obj.setvitrino(1);

                if(main_obj.time_bom_no_()==40)
                {
                    main_obj.setbomno(true);
                    main_obj.setdatbom(false);
                    main_obj.settimebom(0);
                    main_obj.setvitrino(0);
                }
            }
            BombObject bomb = main_obj.getbom();

            for(int i=0; i<25; i++)
            {
                if(gThreat[i].getdichuyen())
                {
                    gThreat[i].SetXY(map_data.start_x_,map_data.start_y_);
                    gThreat[i].dichuyen(map_data,bricks,bomb.GetRect());
                    gThreat[i].Show(gScreen);
                }
            }
            for(int i=0; i<7; i++)
            {
                if(gManhay[i].getdichuyen())
                {
                    gManhay[i].SetXY(map_data.start_x_,map_data.start_y_);
                    gManhay[i].dichuyen(map_data,bricks,bomb.GetRect());
                    gManhay[i].Show(gScreen);
                }
            }
            for(int i=0; i<5; i++)
            {
                if(gMatanghinh[i].getdichuyen())
                {
                    gMatanghinh[i].SetXY(map_data.start_x_,map_data.start_y_);
                    gMatanghinh[i].dichuyen();
                    gMatanghinh[i].Show(gScreen);
                }
            }
            SDL_Rect main_rect=main_obj.GetRect();
            main_rect.w=DOT_WIDTH-20;
            main_rect.h=DOT_HEIGHT-20;
            main_rect.x += 10;
            main_rect.y += 10;

            bool check_main=false;
            int endgame = 0;
            for(int i=0; i<25; i++)
            {
                SDL_Rect threat_rect=gThreat[i].GetRect();
                check_main=SDLCommonFunc::CheckCollision(main_rect,threat_rect);
                if(check_main)
                {
                    die_number++;
                    std::cout<<"nhan vat chet vi quai"<<'\n';
                    mark_value -= 500;
                    endgame = 1;
                    SDL_Delay(2000);

                    main_obj.free();
                    player_power.Decrease();
                    player_power.render(gScreen);
                    Mix_HaltChannel(-1);
                    break;
                }
            }

            bool check_main2 = false;
            for(int j=0; j<7; j++)
            {
                SDL_Rect manhay_rect=gManhay[j].GetRect();

                check_main2=SDLCommonFunc::CheckCollision(main_rect,manhay_rect);
                if(check_main2)
                {
                    die_number++;
                    std::cout<<"nhan vat chet vi ma nhay"<<'\n';
                    mark_value -= 500;
                    endgame = 1;
                    SDL_Delay(2000);
                    main_obj.free();
                    player_power.Decrease();
                    player_power.render(gScreen);
                    Mix_HaltChannel(-1);
                    break;
                }
            }

            bool check_main3 = false;
            for(int j=0; j<5; j++)
            {
                SDL_Rect matanghinh_rect=gMatanghinh[j].GetRect();

                check_main3=SDLCommonFunc::CheckCollision(main_rect,matanghinh_rect);
                //std::cout<<matanghinh_rect.x<<" "<<matanghinh_rect.y<<endl;
                if(check_main3)
                {
                    die_number++;
                    std::cout<<"nhan vat chet vi ma tang hinh"<<'\n';
                    mark_value -= 500;
                    endgame = 1;
                    SDL_Delay(2000);
                    main_obj.free();
                    player_power.Decrease();
                    player_power.render(gScreen);
                    Mix_HaltChannel(-1);
                    break;
                }
            }
            if(endgame == 1)break;

            // check ghost cham main
            SDL_Rect AI_rect = ghostAI.GetRect();
            AI_rect.w /=5;
            AI_rect.h /=2;
            check_main = SDLCommonFunc::CheckCollision1(main_rect,AI_rect);
            if(check_main)
            {
                die_number++;
                std::cout<<"nhan vat chet vi ma"<<'\n';
                mark_value -= 500;
                SDL_Delay(2000);
                main_obj.free();
                player_power.Decrease();
                player_power.render(gScreen);
                Mix_HaltChannel(-1);
                break;
            }


            if(ghostAI.getda_chet()==0 )
            {
                ghostAI.SetXY(map_data.start_x_,map_data.start_y_);
                ghostAI.dichuyen(main_obj, ghost_sound, mute);
                ghostAI.Show(gScreen);
            }


            if(main_obj.getbomno())
            {

                int x1=bomb.toa_do_x();
                int y1=bomb.toa_do_y();
                int x_bom_ngang=x1-70;
                int y_bom_ngang=y1;
                int x_bom_doc=x1;
                int y_bom_doc=y1-70;
                SDL_Rect bom_ngang= {x_bom_ngang,y_bom_ngang,210,70};
                SDL_Rect bom_doc= {x_bom_doc,y_bom_doc,70,210};

                // check quai AI

                bool check_ngang_ai=SDLCommonFunc::CheckCollision1(bom_ngang,AI_rect);
                bool check_doc_ai=SDLCommonFunc::CheckCollision1(bom_doc,AI_rect);
                if(check_ngang_ai||check_doc_ai)
                {
                    //std::cout<<"va cham qua AI";
                    mark_value += 300;
                    ghostAI.free();
                    ghostAI.setda_chet(1);
                }

                //check bom va cham main
                bool check_ngang_main=SDLCommonFunc::CheckCollision1(bom_ngang,main_rect);
                bool check_doc_main=SDLCommonFunc::CheckCollision1(bom_doc,main_rect);
                if(check_ngang_main||check_doc_main)
                {
                    die_number ++;
                    std::cout<<"nhan vat chet vi bom no"<<endl;
                    mark_value -= 500;
                    main_obj.free();
                    SDL_Delay(2000);

                    player_power.Decrease();
                    player_power.render(gScreen);
                    Mix_HaltChannel(-1);
                    break;
                }
                // check bom va cham quai
                for(int i=0; i<25; i++)
                {
                    SDL_Rect quai_rect=gThreat[i].GetRect();
                    bool check_ngang=SDLCommonFunc::CheckCollision1(bom_ngang,quai_rect);
                    bool check_doc=SDLCommonFunc::CheckCollision1(bom_doc,quai_rect);
                    if(check_ngang)
                    {
                        gThreat[i].setdichuyen(false);
                        gThreat[i].free();
                        number_of_threats --;
                        mark_value += 100;
                    }
                    else if(check_doc)
                    {
                        gThreat[i].setdichuyen(false);
                        gThreat[i].free();
                        number_of_threats --;
                        mark_value += 100;
                    }
                }
                //check bom va cham ma nhay
                for(int i=0; i<7; i++)
                {
                    SDL_Rect manhay_rect=gManhay[i].GetRect();
                    bool check_ngang=SDLCommonFunc::CheckCollision1(bom_ngang,manhay_rect);
                    bool check_doc=SDLCommonFunc::CheckCollision1(bom_doc,manhay_rect);
                    if(check_ngang)
                    {
                        gManhay[i].setdichuyen(false);
                        gManhay[i].free();
                        number_of_manhay --;
                        mark_value += 200;
                    }
                    else if(check_doc)
                    {
                        gManhay[i].setdichuyen(false);
                        gManhay[i].free();
                        number_of_manhay --;
                        mark_value += 200;
                    }
                }
                //check bom va cham matanghinh
                for(int i=0; i<5; i++)
                {
                    SDL_Rect matanghinh_rect=gMatanghinh[i].GetRect();
                    bool check_ngang=SDLCommonFunc::CheckCollision1(bom_ngang,matanghinh_rect);
                    bool check_doc=SDLCommonFunc::CheckCollision1(bom_doc,matanghinh_rect);
                    if(check_ngang)
                    {
                        gMatanghinh[i].setdichuyen(false);
                        gMatanghinh[i].free();
                        number_of_matanghinh --;
                        mark_value += 400;
                    }
                    else if(check_doc)
                    {
                        gMatanghinh[i].setdichuyen(false);
                        gMatanghinh[i].free();
                        number_of_matanghinh --;
                        mark_value += 400;
                    }
                }

                main_obj.Bom_no(gScreen,map_data);

                bomb.logicbomno(map_data,bricks);

                main_obj.setbomno(false);

            }

            if(val_time % 60 == 0 && val_time <600)
            {
                ghostAI.setda_chet(0);
                ghostAI.LoadImg("loadimg/ghostAI.png",gScreen);
                ghostAI.SetClip();
                ghostAI.SetToaDo(2240,1470);
                AI_rect.w*=5;
                AI_rect.h*=2;
            }
            if(val_time <= 0)
            {
                quit = true;
                break;
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                time_game.SetText(str_val);
                time_game.LoadFromRenderText(font_,gScreen);
            }

            if(number_of_matanghinh ==0 && number_of_threats == 0 && number_of_manhay == 0 && map_data.tile[main_rect.y/70][main_rect.x/70]==9)
            {

                std::cout<<"YOU WON!"<<endl;
                mark_value += 10*val_time;
                if(mark_value > 9000)
                {
                    if(victory(gScreen,g_win_sound,1)==false)
                        SDL_Delay(1000);
                }
                else
                {
                    if(victory(gScreen,g_win2_sound,2)==false)
                        SDL_Delay(1000);
                }
                player_power.free();
                for(int i = 0; i < 25; i++)
                {
                    gThreat[i].free();
                }
                for(int i = 0; i < 7; i++)
                {
                    gManhay[i].free();
                }
                for(int i = 0; i < 5; i++)
                {
                    gMatanghinh[i].free();
                }

                bricks.freetile_threat();
                gBackground.free();
                time_game.Free();

                close();

                return 0;
            }


            player_power.render(gScreen);

            bricks.setlaimap(map_data);
            bomb.free();

            //Show mark,time
            std::string strMark = std::to_string(mark_value);
            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_, gScreen);
            mark_game.RenderText(gScreen, 300, 20);
            time_game.RenderText(gScreen, 1092, 18);
            SDL_Delay(20);
            SDL_RenderPresent(gScreen);
        }

        ghostAI.free();
        main_obj.free();
    }
    if(die_number == 3)
    {
        if(gameover(gScreen,g_end_sound)==false)
        {
            SDL_Delay(1000);
        }
        player_power.free();
        for(int i = 0; i < 25; i++)
        {
            gThreat[i].free();
        }
        for(int i = 0; i < 7; i++)
        {
            gManhay[i].free();
        }
        for(int i = 0; i < 5; i++)
        {
            gMatanghinh[i].free();
        }

        bricks.freetile_threat();
        gBackground.free();
        time_game.Free();
    }
    close();
    return 0;
}


