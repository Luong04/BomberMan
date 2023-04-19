#include "TextObject.h"

TextObject::TextObject()
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
}

TextObject::~TextObject()
{

}

void TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* texture_surface = TTF_RenderText_Solid(font,str_val_.c_str(),text_color_);
    texture_ = SDL_CreateTextureFromSurface(screen, texture_surface);
    width_ = texture_surface->w;
    height_ = texture_surface->h;

    SDL_FreeSurface(texture_surface);
}

void TextObject::Free()
{
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::SetColor(int type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255,0,0};
        text_color_ = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255,255,255};
        text_color_ = color;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        text_color_ = color;
    }
}

void TextObject::RenderText(SDL_Renderer* screen,int xp, int yp, SDL_Rect* clip, double angle,SDL_Point * center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp,yp,width_,height_};
    if(clip!= NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture_,clip,&renderQuad,angle,center,flip);
}
