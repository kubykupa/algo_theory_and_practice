#include <cassert>
#include <iostream>

class Fibonacci final {
public:
    static int get(int n) {
        assert(n >= 0);
        unsigned int n_2 = 0;
        unsigned int n_1 = 1;
        if (n == 0) return n_2;
        if (n == 1) return n_1;
     
        unsigned int res = 0; 
        for (int i = 2; i <= n; i++) {
            res = n_1 + n_2;
            n_2 = n_1;
            n_1 = res;
        }
        return res;
    }
};

int main(void) {
    // for (int i =0; i <= 40; i++) {
    //     std::cout << i << ": " << Fibonacci::get(i) << std::endl;
    // }
    int n;
    std::cin >> n;
    std::cout << Fibonacci::get(n) << std::endl;
    return 0;
}