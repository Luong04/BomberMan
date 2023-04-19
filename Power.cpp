
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

        for(int i = 0; i < power_list.size();i++)
        {
            rect_.x = power_list.at(i);
            rect_.y = 14;
            rect_.w = 42;
            rect_.h = 35;
            Render(screen);
        }

}

void Power::Init()
{
    number_ = 0;
    if(power_list.size() > 0)
    {
        power_list.clear();
    }

    AddPos(21);
    AddPos(77);
    AddPos(133);
}

void Power::print()
{
    std::cout<<power_list.size()<<"\n";
    for(int i = 0  ; i  < power_list.size();i++)
    {
        std::cout<<power_list.at(i)<<" ";
    }
    std::cout<<" ";
}

void Power::Decrease()
{
    number_ --;
    power_list.pop_back();
}
