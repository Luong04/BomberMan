#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "map.h"
#include "BombObject.h"
#include "Threat.h"
#include "ghostAI.h"
#include "Power.h"

using namespace std;

SDL_Window* gWindow=NULL;
SDL_Renderer* gScreen=NULL;
SDL_Texture* gText=NULL;
SDL_Event gevent;

Mix_Chunk* g_sound_bkgr = NULL;
Mix_Chunk* ghost_sound = NULL;
Mix_Chunk* bom_sound = NULL;
void init()
{
    SDL_INIT_EVERYTHING;
    gWindow=SDL_CreateWindow("BOMBER MAN",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    gScreen=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    //int Mix_AllocateChannels(3);
    g_sound_bkgr = Mix_LoadWAV("loadsound/nhacnen.wav");
    ghost_sound = Mix_LoadWAV("loadsound/ghost1loc.wav");
    bom_sound = Mix_LoadWAV("loadsound/boom.wav");

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

    SDL_Quit();
    Mix_Quit();
}
int main(int argc,char* args[])
{
    init();

    Power player_power;
    int die_number = 0;
    while(die_number <= 2 )
    {
        BaseObject gBackground;
        MainObject main_obj;
        Threat gThreat[25];
        GameMap bricks;
        Ghost ghostAI;
        Support win;

        gBackground.LoadImg("loadimg/bkgr.png",gScreen);
        main_obj.LoadImg("loadimg/main.png",gScreen);
        main_obj.SetClip();
        for(int i=0; i<25; i++)
        {
            gThreat[i].LoadImg("loadimg/threat.png",gScreen);
            gThreat[i].SetClip();
        }
        ghostAI.LoadImg("loadimg/ghostAI.png",gScreen);
        bricks.LoadMap("map1.txt");
        bricks.LoadTiles(gScreen);
        win.LoadImg("loadimg/qua_man.png", gScreen);
        player_power.LoadImg("loadimg/power.png",gScreen);

        int number_of_threats = 25;

        Mix_PlayChannel(-1,g_sound_bkgr,-1);
        player_power.Init();
        main_obj.settocdo(5);
        gThreat[0].SetToaDo(670,140);
        gThreat[1].SetToaDo(210,140);
        gThreat[2].SetToaDo(210,560);
        gThreat[3].SetToaDo(770,140);
        gThreat[4].SetToaDo(490,280);
        gThreat[5].SetToaDo(1190,140);
        gThreat[6].SetToaDo(350,1120);
        gThreat[7].SetToaDo(1190,1330);
        gThreat[8].SetToaDo(910,70);
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
        ghostAI.SetClip();
        bool quit=false;

        while(!quit)
        {

            while(SDL_PollEvent(&gevent)!=0)
            {
                if(gevent.type==SDL_QUIT)
                {
                    die_number = 3;
                    quit=true;
                }
                main_obj.handle(gevent,gScreen);
            }


            //bricks.DrawMap(gScreen,win);
            Map map_data = bricks.getMap();
            //show player power

            main_obj.SetXY(map_data.start_x_,map_data.start_y_);
            main_obj.dichuyen(map_data,bricks);

            gBackground.Render(gScreen);
            main_obj.Show(gScreen);
            bricks.DrawMap(gScreen,win, map_data);

            if(main_obj.getdatbom())
            {
                main_obj.DatBom(gScreen, map_data,bom_sound);

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
            SDL_Rect main_rect=main_obj.GetRect();
            main_rect.w=DOT_WIDTH;
            main_rect.h=DOT_HEIGHT;

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
                    endgame = 1;
                    SDL_Delay(2000);
                    main_obj.free();
                    player_power.Decrease();

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
                SDL_Delay(2000);
                main_obj.free();
                player_power.Decrease();

                Mix_HaltChannel(-1);
                break;
            }


            if(ghostAI.getda_chet()==0 )
            {
                ghostAI.SetXY(map_data.start_x_,map_data.start_y_);
                ghostAI.dichuyen(main_obj, ghost_sound);
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
                    SDL_Delay(2000);
                    main_obj.free();
                    player_power.Decrease();
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
                    }
                    else if(check_doc)
                    {
                        gThreat[i].setdichuyen(false);
                        gThreat[i].free();
                        number_of_threats --;
                    }
                }

                main_obj.Bom_no(gScreen,map_data);

                bomb.logicbomno(map_data,bricks);

                main_obj.setbomno(false);

            }
            SDL_Rect win_rect = win.GetRect();


            if(number_of_threats == 0 && SDLCommonFunc::CheckCollision1(main_rect,win_rect)==1)
            {

                cout<<"YOU WON!"<<endl;
                close();

                return 0;
            }
            bricks.setlaimap(map_data);

            SDL_Delay(20);
            SDL_RenderPresent(gScreen);
        }
        for(int i = 0; i < 25; i++)
        {
            gThreat[i].free();
        }
        ghostAI.free();
        main_obj.free();
        bricks.freetile_threat();
    }

    close();
    return 0;
}


