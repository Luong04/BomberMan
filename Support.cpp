#include "Support.h"


Support::Support() {
  x_toa_do_=0;
  y_toa_do_=0;
}
void Support::settoado_x_y(int x,int y) {
   x_toa_do_=x;
   y_toa_do_=y;
   rect_.x=x*70;
   rect_.y=y*70;
}
void Support::delete_vat_pham() {
  free();
}
