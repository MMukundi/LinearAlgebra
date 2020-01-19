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
Vector<Dimensions> Vector<Dimensions>::clone() const
{
    Vector v = Vector();
    int size = sizeof(NumericalType) * dimensions;
    v.dimensions = dimensions;
    v.components = (NumericalType *)malloc(size);
    memcpy(v.components, components, size);
    return v;
};

template <int Dimensions>
std::string Vector<Dimensions>::toString() const
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
bool areLinearlyDependent(Vector<Dimensions> vectors[])
{


    auto a = vectors[0];
    auto b = vectors[1];
    float scalar;
    if (a.dimensions!=b.dimensions)
        return false;
    int d = 0;
    for (; d < Dimensions; d++)
    {
        if (a.components[d] == 0)
        {
            if (b.components[d] == 0 && d == Dimensions - 1)
                return false;
        }
        else
        {
            scalar = b.components[d] / a.components[d];
            break;
        }
    }

    for (d++; d < Dimensions; d++)
    {
        if (a.components[d] == 0)
        {
            if (b.components[d] != 0)
                return false;
        }
        else if (scalar * a.components[d] != b.components[d])
        {
            printf("%f * %f != %f\n",scalar, a.components[d], b.components[d]);
            return false;
        }
    }
    return true;
}

template <int Dimensions>
Space<Dimensions> &spanOf(Vector<Dimensions> v[])
{
    std::list<LinearAlgebra::Vector<Dimensions>> list;

    int i = 0;

    auto curr = 0;
    auto other = 1;

    bool valid = true;
    for (;curr<Dimensions; curr++)
    {
        valid = true;
        for (other = curr; other <Dimensions; other++)
        {
            if (areLinearlyDependent({*v[curr],*v[other]}))
            {
                printf("%s and %s are linearly dependent", (*v[curr]).toString().c_str(), (*v[other]).toString().c_str());
                valid = false;
            }
        }
        if (!valid)
            break;

        printf("%s", (v[curr])->toString().c_str());
        list.push_back(*v[curr]);
    };
    //constexpr auto size = 4;
    return *new Space<Dimensions>(Basis<Dimensions>(list));
}

} //namespace LinearAlgebra