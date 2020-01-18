#include "LinAlg.h"
#include <iostream>
#include <cmath>

using namespace LinearAlgebra;

int main(void){
    Vector<3> a({1,2,3});
    Vector<3> b=Vector<3>::multiply(a,M_PI);
    Vector<3> c={3,2,1};
    std::cout<<"Before:"<<a.toString();
    std::cout<<", AfterDoubling:"<<b.toString();
    std::cout<<"; ab:"<<a.areLinearlyIndependent(b);
    std::cout<<", bc:"<<b.areLinearlyIndependent(c);
    std::cout<<", ac:"<<a.areLinearlyIndependent(c)<<std::endl;
    std::cout<<"span:"<<Vector<3>::spanOf({a,b,c}).toString()<<std::endl;
}