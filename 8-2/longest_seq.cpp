#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;
using T = int;
using V = vector<T>;

void print(const V& vec) {
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

V solve_nn(const V&vec) {
    const size_t N = vec.size();
    V DP(N, 1);

    for (size_t i = 1; i < N; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (vec[j] >= vec[i] && DP[j] + 1 >= DP[i]) {
                DP[i] = DP[j] + 1;
            }
        }
    }

    // print(vec);
    // print(DP);

    // find max len sequence ends in element
    int maxLen = DP[0];
    int index = 0;
    for (size_t i = 1; i < N; ++i) {
        if (DP[i] > maxLen) {
            maxLen = DP[i];
            index = i;
        }
    }
    // cout << "found len: " << maxLen << endl;

    // reconsturct
    V ans;
    ans.push_back(index);
    while (--index >= 0) {
        if (DP[ans.back()] == DP[index] + 1 && vec[index] >= vec[ans.back()]) {
            ans.push_back(index);
        }
    }
    reverse(ans.begin(), ans.end());    

    // for (auto v: ans) {
    //     cout << vec[v] << " ";
    // } cout << endl;
    return ans;
}

V solve_nlogn(const V& X) {
    const int INF = INT32_MAX;
    const int N = X.size();
    // M[l] - индекс последнего элемента в неубывающей
    // подпоследовательности длины l оканчивающейся X[i]
    V M(N+1, -1);
    V P(N, INF);

    M[0] = INF;

    // cout << "IN: ";
    // print(X);
    int L = 0;
    for (int i = 0; i < N; ++i) {
        int l = 1, r = L, m;
        // считаем что у нас есть M[], нужно понять куда попадет X[i]
        // найдем такое l: X[M[l - 1]] >= X[i] > X[M[l]]
        while (l <= r) {
            m = l + (r - l) / 2;
            if (X[M[m]] >= X[i]) { // >= определяет 'невозрастаемость'
                l = m+1;
            } else {
                r = m-1;
            }
        }
        // обновляем максимальное значение в последовательности длины l
        M[l] = i;

        // cout << "X[" << i<< "]=" << X[i] << " ";
        // for (int j = 1; j <= L ; ++j) {
        //     cout << M[j] << "->" << X[M[j]] << " ";
        // }

        P[i] = M[l-1]; // для X[i] элемента предыдущим элементом будет
                       // последний элемент из последовательности длиной l-1
        // cout << " parents: ";
        // for (int j = 0; j <= i; ++j) {
        //     // cout << X[j] << "<-";
        //     if (P[j] == INF) cout << "[-]";
        //     else cout << X[P[j]];
        //     cout << " ";
        // } cout << endl;

        if (l > L) {
            // отслеживаем максимальную длину, M[L] - элемент в котором
            // заканчивается самая длинная неубывающая подпоследовательность
            L = l;
        }
    }
    // print(P);
    // cout << "Length: " << L << endl;
    V ans(L);
    for (int j = L-1, i = M[L]; j >= 0 && i != INF; --j) {
        ans[j] = i;
        // cout << "X[" << i << "] = " << X[i] << "<- P[" << i << "]=" << P[i] << endl;
        i = P[i];
    }

    // cout << endl << "answer: ";
    // for (auto v: ans) {
    //     cout << X[v] << " ";
    // } cout << endl;

    return ans;
}

#include <ctime>
int Random(int min, int max) {
    return min + rand() % (max - min);
}

void brute() {
    const int MAX = 10000;
    // const int MAX_VAL = 1000000000;
    const int MAX_VAL = 100;
    while (1) {
        int N = Random(2, MAX);

        V vec(N);
        for (auto& v : vec) {
            v = Random(1, MAX_VAL);
        }

        auto ans = solve_nlogn(vec);
        for (size_t i = 1; i < ans.size(); ++i) {
            if (vec[ans[i - 1]] < vec[ans[i]]) {
                cerr << "BAD ANS" << endl
                     << "vec[" << ans[i - 1] << "] = " << vec[ans[i-1]] << " < "
                     << "vec[" << ans[i] << "] = " << vec[ans[i]] << endl;

                print(vec);
                return;
            }
        }
    }
}

int main(void) {
    if (0) {
        // solve_nlogn({7, 6, 2, 3, 8, 4, 5});
        brute();
        return 1;
    }

    size_t number_count;
    std::cin >> number_count;
    std::vector<int> numbers(number_count);
    for (auto &number : numbers) {
        std::cin >> number;
    }

    auto ans = solve_nlogn(numbers);
    cout << ans.size() << endl;
    for (auto v : ans) {
        cout << v + 1 << " ";
    }
    cout << endl;
}
