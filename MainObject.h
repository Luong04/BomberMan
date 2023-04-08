#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BombObject.h"
#include "map.h"
class MainObject:public BaseObject
{
public:
    MainObject();
    ~MainObject() {;}
    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void handle(SDL_Event &e,SDL_Renderer* screen);
    void SetClip();

    float posx()
    {
        return x_pos_;
    }
    float posy()
    {
        return y_pos_;
    }
    void SetToaDo(const int &x,const int &y)
    {
        x_pos_=x;
        y_pos_=y;
    }
    void dichuyen(Map& map_data,GameMap &game_map);
    void setFramebom(int x)
    {
        bomb.SetFrame(x);
    }
    bool getbomno()
    {
        return bomb.getbomno1();
    }
    void Bom_no(SDL_Renderer* screen, Map &map_data_);
    void DatBom(SDL_Renderer* screen, Map &map_data_, Mix_Chunk* bom);
    bool getdatbom()
    {
        return dat_bom;
    }
    int set_x_bom_()
    {
        return set_x_bom;
    }
    int set_y_bom_()
    {
        return set_y_bom;
    }

    void settocdo(int x)
    {
        toc_do=x;
    }
    int gettocdo()
    {
        return toc_do;
    }

    void setbomno(bool t)
    {
        bomb.SetBomno(t);
    }
    void setdatbom(bool t)
    {
        dat_bom=t;
    }
    void settimebom(int tmp)
    {
        time_bom_no=tmp;
    }
    int time_bom_no_()
    {
        return time_bom_no;
    }
    BombObject getbom()
    {
        return bomb;
    }
    void setvitrino(bool x)
    {
        vitrino = x;
    }

    void sety_loadanh(int k)
    {
        y_loadanh = k;
    }
    int gety_loadanh() {return y_loadanh;}

    void CenterOnMap(Map& map_data);
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    Input input_type;
    int frame_;
    int status_;

    int set_x_bom;
    int set_y_bom;

    int time_bom_no;

    bool dat_bom;
    BombObject bomb;
    SDL_Rect clip_[4][5];

    int toc_do;

    bool vitrino;
    int y_loadanh;
};
#endif // MAIN_OBJECT_H_
