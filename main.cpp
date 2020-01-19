#include "LinAlg.hpp"
#include <iostream>
#include <cmath>

using namespace LinearAlgebra;

int main(void)
{
    Vector<3> a({1, 2, 3});
    Vector<3> b = Vector<3>::multiply(a, M_PI);
    Vector<3> c = {3, 2, 1};
    auto s = Set<Vector<3>>{&a,&b,&c};
    for (auto abc : s.toArray())
    {
        std::cout << "SetMemb:" << abc.toString() << "\n";
    }
    std::cout << "Before:" << a.toString();
    std::cout << ", AfterDoubling:" << b.toString();
    //std::cout << "; ab:" << areLinearlyDependent({a, b, c}) << std::endl;
    //std::cout << "span:" << spanOf({a, b, c}).toString() << std::endl;
}