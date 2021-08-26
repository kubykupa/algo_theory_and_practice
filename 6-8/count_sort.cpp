#include <iostream>
#include <vector>

using namespace std;

void count_sort(vector<int>& vec) {
    vector<int> digits(11);
    for (auto v : vec) {
        ++digits[v];
    }
    size_t i = 0;
    for (size_t j = 0; j < digits.size(); ++j) {
        while (digits[j]-- > 0) {
            vec[i++] = j;
        }
    }
}

void count_sort_2(vector<int>& vec) {
    vector<int> digits(11);
    for (auto v : vec) {
        ++digits[v];
    }
    for (size_t i = 2; i < 11; ++i) {
        digits[i] += digits[i - 1];
    }
    vector<int> tmp(vec.size());
    for (int i = vec.size() - 1; i >= 0; i--) {
        --digits[vec[i]];
        tmp[digits[vec[i]]] = vec[i];
    }

    vec = move(tmp);
}

int main() {
    int N;
    cin >> N;

    vector<int> vec(N);
    for (int i = 0; i < N; ++i) {
        cin >> vec[i];
    }

    count_sort_2(vec);

    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
