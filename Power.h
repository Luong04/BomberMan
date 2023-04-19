#ifndef POWER_H
#define POWER_H
#include "BaseObject.h"
#include <vector>
class Power : public BaseObject
{
public:
    Power();
    ~Power();
    void SetNumber(const int&num){number_ = num;}
    void AddPos(const int& xpos);
    void render(SDL_Renderer* screen);
    void Init();
    void Decrease();
    void print();
private:
    int number_;
    std::vector<int> power_list;
};

#endif // POWER_H
