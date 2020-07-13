#include <iostream>
#include "bitset_integer.h"

const size_t N=3000; // bit size of integers

bi<N> pow(bi<N> x, int y){
    bi<N> ret = x;
    for(int i = 1; i < y; i++){
        ret *= x;
    }
    return ret;
}

bi<N> f(int x){
    bi<N> frac1(x);
    bi<N> frac2(1); 
    bi<N> base = pow(bi<N>(10), 500);
    bi<N> ret = base / x;
    bi<N> x2 = pow(x, 2);

    for(int i = 0; ; i++) {
        frac1 *= x2;
        frac2 += bi<N>(2);
        bi<N> term = base / (frac1 * frac2);
        if(term == bi<N>(0)){
            break;
        }
        if(i % 2 == 0){
            ret -= term;
        }else{
            ret += term;
        }
    }
    return ret;
}

int main(){
    bi<N> pi = bi<N>(4) * (bi<N>(4) * f(5) - f(239));
    std::cout << pi.to_string() << std::endl;
}