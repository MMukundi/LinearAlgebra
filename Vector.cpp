#include "Vector.h"
#include "Space.h"
#include "Set.h"

#include <sstream>
#include <iostream>

namespace LinearAlgebra
{
template <int Dimensions>
Vector<Dimensions>::Vector(std::initializer_list<NumericalType> l)
{
    dimensions = (int)l.size();
    //printf("\n-%d-%d-%d\n",l.size(),sizeof(NumericalType),dimensions);
    components = (NumericalType *)malloc(dimensions * sizeof(NumericalType));
    auto c = l.begin();
    for (int n = 0; n < dimensions; n++)
    {
        components[n] = *(c++);
    };
}

template <int Dimensions>
Vector<Dimensions>::~Vector()
{
    //free(components);
}

template <int Dimensions>
Vector<Dimensions> &Vector<Dimensions>::multiply(NumericalType s)
{
    for (int d = 0; d < dimensions; d++)
    {
        components[d] *= s;
    }
    return *this;
};
template <int D>
Vector<D> Vector<D>::multiply(Vector<D> &v_, NumericalType s)
{
    Vector v = v_.clone();
    for (int d = 0; d < v.dimensions; d++)
    {
        v.components[d] *= s;
    }
    return v;
};

template <int Dimensions>
Vector<Dimensions> Vector<Dimensions>::clone()
{
    Vector v = Vector();
    int size = sizeof(NumericalType) * dimensions;
    v.dimensions = dimensions;
    v.components = (NumericalType *)malloc(size);
    memcpy(v.components, components, size);
    return v;
};

template <int Dimensions>
bool Vector<Dimensions>::areLinearlyIndependent(Vector<Dimensions> &v)
{
    if (v.dimensions != dimensions)
        return false;

    NumericalType scalar;
    int d = 0;
    for (; d < dimensions; d++)
    {
        if (components[d] == 0)
        {
            if (v.components[d] == 0 && d == dimensions - 1)
                return false;
        }
        else
        {
            scalar = v.components[d] / components[d];
            break;
        }
    }

    for (d++; d < dimensions; d++)
    {
        if (components[d] == 0)
        {
            if (v.components[d] != 0)
                return false;
        }
        else if (scalar * components[d] != v.components[d])
            return false;
    }
    return true;
}

template <int Dimensions>
std::string Vector<Dimensions>::toString()
{
    if (dimensions == 0)
        return "[]";
    char *cStr;
    const char *c;
    std::ostringstream s;
    s << "[";
    int d = 0;
    for (; d < dimensions - 1; d++)
    {
        s << components[d] << ", ";
    }
    s << components[d] << ']';
    return s.str();
}

template <int Dimensions>
Space<Dimensions> &Vector<Dimensions>::spanOf(std::initializer_list<Vector> v)
{
    std::vector<LinearAlgebra::Vector<Dimensions>> list;
    int i = 0;
    for (auto a : v)
    {
        bool k = true;
        for (auto other : v)
        {
            if (&a != &other)
                if(!a.areLinearlyIndependent(other))
                    k = false;
        }
        if (k)
        {
            list.at(i++)=a;
        }
    };
    constexpr auto size = 4;
    return *new Space<std::size(list)>(Basis<std::size(list)>(list));
}

} //namespace LinearAlgebra