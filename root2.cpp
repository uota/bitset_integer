#include <iostream>
#include "bitset_integer.h"

const size_t N=15000; // bit size of integers

bi<N> pow(bi<N> x, int y){
    bi<N> ret = x;
    for(int i = 1; i < y; i++){
        ret *= x;
    }
    return ret;
}

// binary search
int main(){
    bi<N> target = bi<N>(2) * pow(bi<N>(10), 1000);
    bi<N> l(0);
    bi<N> r = target;
    while(r >= l){
        bi<N> mid = l + (r - l) / bi<N>(2);
        if(mid * mid > target){
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    std::cout << r.to_string() << std::endl;
}