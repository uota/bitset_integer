#include <iostream>
#include "bitset_integer.h"

int main(){
    const size_t N=10000; // bit size of integers
    bi<N> n(1);
    for(int i = 2; i < 1000; i++){
        n *= bi<N>(i);
    }
    std::cout << n.to_string() << std::endl;
    return 0;
}