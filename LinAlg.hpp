#if !defined(LINEARALGEBRA_H)
#define LINEARALGEBRA_H
#include <initializer_list>
#include <array>
#include <functional>

namespace LinearAlgebra
{
    template <template <class, typename...> typename Cont,typename DataType, typename... Fargs>
    bool testAll(Cont<DataType, Fargs...> data, std::function<bool(DataType)> predicate = [](DataType d){return &d!=nullptr;}){
        for(DataType v: data){
            if(!predicate(v)) return false;
        }
        return true;
    }
} // namespace LinearAlgebra

#include "Vector.h"
#include "Space.h"

#endif // LINEARALGEBRA_H
