#include <math.h>
#include "source.h"
#include "environment.h"

namespace fansnn{

DC::DC(float I){
    this->I = I;
}

float DC::update(void){
    return I;
}

AC::AC(float A, int f, int phi){
    this->A = A;
    this->dphi = 360.0/f;
    this->phi = phi;
}

float AC::update(void){
    this->phi += this->dphi;
    return sin(this->phi)*this->A;
}

}