#if !defined(VECTOR_H)
#define VECTOR_H

#include <stdlib.h>
#include <list>
#include <string>
#include <type_traits>

template <typename T, typename... Ts>
using all = typename std::enable_if<std::conjunction<std::is_convertible<Ts, T>...>::value>::type;

namespace LinearAlgebra
{
/** A Vector in n-dimentional space, a space with n perpendicular axes, represented by a direction and a magnitude
 */
template<int Dimensions>
class Space;


template<int Dimensions>
class Vector
{
    typedef double NumericalType;

public:
    /** Returns a Vector with the provided list as the components of the vector
    */
    Vector(std::initializer_list<NumericalType> l);

    Vector(){};
    Vector(Vector *){};

    ~Vector();

    //The number of dimensions in which this Vector exists
    int dimensions = -1;

    //The signed coefficients of each of the Vector space's basis vectors
    NumericalType *components = nullptr;

    /** Makes this Vector the sum of this vector and another vector [associative and communicative]
     */
    Vector &add(Vector *v);

    /** Makes this Vector the product of a scalar and itself [associative, communicative, and distributive ]
     */
    Vector &multiply(NumericalType s);

    /** Makes this Vector its own additive inverse
    */
    Vector &negate()
    {
        this->multiply(-1);
        return *this;
    };

    /** Makes this vector the sum of this Vector and another Vector [associative and communicative]
     */
    bool areLinearlyIndependent(Vector &v);

    /** Returns an exact copy of this Vector
     */
    Vector clone();
    /** Returns a text representation of this Vector
     */
    std::string toString();

    /***/
    static const Vector *ORIGIN;

    static Space<Dimensions> &spanOf(std::initializer_list<Vector> v);

    /** Returns the sum of the vector and another vector [associative and communicative]
     */
    static Vector add(Vector &v, Vector &w);

    /** The associative, communicative, and distributive multiplication of a scalar and a Vector
     */
    static Vector multiply(Vector &v, NumericalType s);

    /** The additive inverse of a vector
     */
    static Vector negate(Vector &v);

    Vector operator*(int s)
    {
        return multiply(*this, s);
    }
};
} // namespace LinearAlgebra
#include "Space.h"
#include "Vector.cpp"
#endif // VECTOR_H