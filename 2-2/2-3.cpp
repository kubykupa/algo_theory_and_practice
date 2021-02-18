#include <cassert>
#include <iostream>
#include <vector>

class Fibonacci final {
public:
    static int get_remainder_fast(int64_t n, int m) {
        assert(n >= 1);
        assert(m >= 2);
        if (n == 0) return 0;
        if (n == 1) return 1;

        std::vector<int> rems;
        rems.push_back(0);
        rems.push_back(1);
        rems.push_back(1);
     
        int res = 0; 
        int i = rems.size() - 1;
        while (i <= 6 * m) {
            res = (rems[i] + rems[i-1]) % m;
            rems.push_back(res);
            ++i;

            // std::cout << i << ": " << res << std::endl;

            if (rems[i] == 1 && rems[i-1] == 1 && rems[i-2] == 0) {
                break;
            }
        }
        
        // for (int v: rems) {
        //     std::cout << v << " ";
        // }
        // std::cout << std::endl;

        int period = i - 2;
        // std::cout << "i - " << i << " period - " << period << std::endl;

        int index = n % period;
        // std::cout << "n % d - " << index << std::endl;

        // std::cout << "rems[n % d] - " << rems[index] << std::endl;
        return rems[index];
    }

    static int get_remainder(int64_t n, int m) {
        assert(n >= 1);
        assert(m >= 2);

        int n_2 = 0;
        int n_1 = 1;
        if (n == 0) return n_2;
        if (n == 1) return n_1;
     
        unsigned int res = 0; 
        for (int i = 2; i <= n; i++) {
            res = (n_1 + n_2) % m;
            n_2 = n_1;
            n_1 = res;
        }
        return res;
    }
};

int main(void) {
    // assert(Fibonacci::get_remainder_fast(9, 2) == 0);
    // assert(Fibonacci::get_remainder_fast(10, 2) == 1);
    // assert(Fibonacci::get_remainder_fast(1025, 55) == 5);
    // assert(Fibonacci::get_remainder_fast(12589, 369) == 89);
    // assert(Fibonacci::get_remainder_fast(1598753, 25897) == 20305);
    // assert(Fibonacci::get_remainder_fast(60282445765134413, 2263) == 974);
    // assert(Fibonacci::get_remainder_fast(25, 97) == 44);

    // for (int n = 1; n <= 2000; n++) {
    //     std::cout << "n:" << n << ' ';
    //     std::cout.flush();

    //     for (int m = 2; m <= 10000; m++) {
    //         // std::cout << "m:" << m << "  " << std::endl;
    //         int r1 = Fibonacci::get_remainder(n, m);
    //         int r2 = Fibonacci::get_remainder_fast(n, m);
    //         if (r1 != r2) {
    //             std::cout << std::endl << r1 << " != " << r2 << "   n: " << n << " m: " << m << std::endl;
    //         }
    //     }
    // }

    int64_t n;
    int m;
    std::cin >> n >> m;
    std::cout << Fibonacci::get_remainder_fast(n, m) << std::endl;
    return 0;
}