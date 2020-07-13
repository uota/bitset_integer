#include <iostream>
#include <cassert>
#include <string>

#include "bitset_integer.h"

int main(){
    const size_t N=16; // bit size of integers

bi<128> x(12345); // Initialize a 128-bit integer by int.
bi<128> y("-1234567890"); // Initialize a 128-bit integer by string.

x += y; // Calculate between bitset integers.

std::cout << x.to_llong() << std::endl; // Conversion to long long int.
std::cout << x.to_string() << std::endl; // Conversion to string.

    for(int i = -100; i <= 100; i++){
        assert(bi<N>(i).to_llong() == i);
        assert(bi<N>(std::to_string(i)).to_llong() == i);
        assert(bi<N>(i).to_string() == std::to_string(i));

        for(int j = -100; j <= 100; j++){
            bi<N> a(i);
            bi<N> b(j);
            bi<N> c;

            assert((a + b).to_llong() == (i + j));
            assert((a - b).to_llong()  == (i - j));
            assert((a * b).to_llong()  == (i * j));
            if(j != 0) assert((a / b).to_llong()  == (i / j));
            if(j != 0) assert((a % b).to_llong()  == (i % j));

            c = a; c += b;
            assert(c.to_llong()  == (i + j));
            c = a; c -= b;
            assert(c.to_llong()  == (i - j));
            c = a; c *= b;
            assert(c.to_llong()  == (i * j));
            if(j!=0){
                c = a; c /= b;
                assert((a / b).to_llong()  == (i / j));
            }
            if(j!=0){
                c = a; c %= b;
                assert((a % b).to_llong()  == (i % j));
            }

            assert((a == b) == (i == j));
            assert((a != b) == (i != j));
            assert((a < b) == (i < j));
            assert((a > b) == (i > j));
            assert((a <= b) == (i <= j));
            assert((a >= b) == (i >= j));
        }
    }
    std::cout << "test completed." << std::endl;

    return 0;
}
