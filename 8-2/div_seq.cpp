#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

int get_length_of_longest_divisible_subsequence(const std::vector<int> &numbers) {
    const size_t N = numbers.size();
    vector<int> DP(N, 1);

    for (size_t i = 1; i < N; ++i) {
        DP[i] = 1;
        for (size_t j = 0; j < i; ++j) {
            if (numbers[i] % numbers[j] == 0 && DP[j] + 1 >= DP[i]) {
                DP[i] = DP[j] + 1;
            }
        }
    }

    // print(numbers);
    // print(DP);

    int maxLen = DP[0];
    for (size_t i = 1; i < N; ++i) {
        if (DP[i] > maxLen) {
            maxLen = DP[i];
        }
    }
    return maxLen;
}

int main(void) {
    size_t number_count;
    std::cin >> number_count;
    std::vector<int> numbers(number_count);
    for (auto &number : numbers) {
        std::cin >> number;
    }

    std::cout << get_length_of_longest_divisible_subsequence(numbers) << std::endl;
}
