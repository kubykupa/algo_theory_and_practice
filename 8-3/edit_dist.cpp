#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const vector<int>& vec) {
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

int get_levenshtein_distance(const string &a, const string &b) {
    if (a.empty() || b.empty()) {
        return a.size() + b.size();
    }

    int aL = a.size() + 1;
    int bL = b.size() + 1;

    vector<int> prev(aL), curr(aL);
    for (int i = 0; i < aL; ++i) {
        prev[i] = i;
    }

    // cout << aL << ":" << a << endl << bL << ":" << b << endl;
    // print(prev);
    for (int r = 1; r < bL; ++r) {
        curr[0] = r;
        for (int c = 1; c < aL; ++c) {
            int diff = a[c - 1] != b[r - 1];
            curr[c] = min({prev[c] + 1,       // вставка
                           curr[c - 1] + 1,   // удаление
                           prev[c - 1] + diff // замена/совпадение
                          });
        }
        // print(curr);
        swap(curr, prev);
    }
    return prev.back();
}

int main(void) {
    std::string str1;
    std::string str2;

    std::cin >> str1 >> str2;  

    std::cout << get_levenshtein_distance(str1, str2) << std::endl;
    return 0;
}
