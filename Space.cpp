#include "LinAlg.h"
#include "Set.h"

namespace LinearAlgebra
{
template<int D>
std::string Space<D>::toString(){
   // printf("%s","FFFF");
    std::string s;
    for(auto b: basis.vectors) s+=b.toString();
    return s;
}

} // namespace LinearAlgebra
