#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "BaseObject.h"
#include <string>
class TextObject : public BaseObject
{
public:
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    TextObject();
    ~TextObject();

    void LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void SetText(const std::string& text){str_val_ = text;}
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    int GetWidth()const {return width_;}
    int GetHeight() const {return height_;}

    std::string GetText() const {return str_val_;}
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif // TEXT_OBJECT_H_
