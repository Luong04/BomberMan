#ifndef SUPPORT_H_
#define SUPPORT_H_
#include "CommonFunc.h"
#include "BaseObject.h"

class Support : public BaseObject{
 public:
     Support();
     ~Support(){};
     void settoado_x_y(int x,int y);
     void delete_vat_pham();
 private:
    bool is_ma;
    int x_toa_do_;
    int y_toa_do_;
};
#endif // SUPPORT_H_
