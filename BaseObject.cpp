
#include "BaseObject.h"
BaseObject::BaseObject() {
   p_object_=NULL;
   rect_.x=0;
   rect_.y=0;
   rect_.w=0;
   rect_.h=0;
}
BaseObject::~BaseObject()
{
    free();
}
bool BaseObject::LoadImg(std::string path,SDL_Renderer *screen)
{
    SDL_Texture* newtext=NULL;
    SDL_Surface* load_surface=IMG_Load(path.c_str());
    if(load_surface!=NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE,SDL_MapRGB(load_surface->format,0,0xFF,0xFF));

        newtext=SDL_CreateTextureFromSurface(screen,load_surface);
        if(newtext!=NULL)
        {
            rect_.w=load_surface->w;
            rect_.h=load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object_=newtext;
    return p_object_!=NULL;
}
void BaseObject::Render(SDL_Renderer* des)
{
    SDL_Rect quad={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_object_,NULL,&quad);
}

void BaseObject::free()
{
    if(p_object_!=NULL) {
        SDL_DestroyTexture(p_object_);
        p_object_=NULL;
        rect_.x=-70;
        rect_.y=-70;
        rect_.w=0;
        rect_.h=0;
    }
}
