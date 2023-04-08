
#include "Power.h"

Power::Power()
{

}

Power::~Power()
{

}

void Power::AddPos(const int &xpos)
{
    power_list.push_back(xpos);
}

void Power::render(SDL_Renderer* screen)
{
    if(number_ == power_list.size())
    {
        for(int i = 0; i < power_list.size();i++)
        {
            rect_.x = power_list.at(i);
            rect_.y = 0;
            rect_.w = 20;
            rect_.h = 25;
            Render(screen);
        }
    }
}

void Power::Init()
{
    number_ = 3;
    if(power_list.size() > 0)
    {
        power_list.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void Power::Decrease()
{
    number_ --;
    power_list.pop_back();
}
