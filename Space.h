#if !defined(SPACE_H)
#define SPACE_H
#include <list>
#include <initializer_list>

namespace LinearAlgebra
{

template <int Dimensions>
class Basis
{
public:
    LinearAlgebra::Vector<Dimensions> vectors[Dimensions];
    static std::runtime_error ConstructionError(int s)
    {
        throw std::runtime_error("Only given " + std::to_string(s) + 
        ", not enough basis vectors to initialize a " + std::to_string(Dimensions) + " dimensional space");
    }
    Basis(std::array<Vector<Dimensions>, Dimensions> l)
    {
        int i = 0;
        for (auto a : l)
        {
            vectors[i] = a;
            if (++i > Dimensions)
                return;
        }
        if (i < Dimensions)
        {
        }
    };

    Basis(std::initializer_list<Vector<Dimensions>> l)
    {
        int i = 0;
        for (auto a : l)
        {
            vectors[i] = a;
            if (++i > Dimensions)
                return;
        }
        if (i < Dimensions)
        {
            throw ConstructionError(std::size(l));
        }
    };

    template <template <class, typename...> typename Cont, typename... Fargs>
    Basis(Cont<Vector<Dimensions>, Fargs...> l)
    {
        int i = 0;
        for (auto a : l)
        {
            vectors[i] = a;
            if (++i > Dimensions)
                return;
        }
        if (i < Dimensions)
        {
            throw ConstructionError(std::size(l));
        }
    };
};

template <int Dimensions>
class Space
{
public:
    static inline Basis<3> R3BASIS{Vector<3>{1, 0, 0}, Vector<3>{0, 1, 0}, Vector<3>{0, 0, 1}};
    Basis<Dimensions> basis;
    int dimensions = Dimensions;
    Space(Basis<Dimensions> b = R3BASIS) : basis(b)
    {
    }
    std::string toString();
};
} // namespace LinearAlgebra
#include "Vector.h"
#include "Space.cpp"
#endif