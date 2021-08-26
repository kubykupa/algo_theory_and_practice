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

int backpack(int maxWeight, const vector<int>& items) {
    // [максимальный вес, вес если взять i предмет]
    const int N = items.size() + 1;
    ++maxWeight;
    vector<vector<int>> D(maxWeight); 

    for (auto& weight: D) {
        weight.resize(N, 0);
    }

    for (int i = 1; i < N; ++i) {
        for (int w = 1; w < maxWeight; ++w) {
            // берем оптимальное значение без i-го item
            D[w][i] = D[w][i - 1];
            // можно ли на этой вместимости w взять i-й item?
            int wi = items[i - 1];
            if (wi <= w) {
                D[w][i] = max(
                    D[w][i],
                    D[w - wi][i - 1] + wi
                );
            }
        }
    }

    return D.back().back();
}

int main() {
    int W, N;
    cin >> W;
    cin >> N;
    vector<int> weights(N);
    for (auto& w: weights) {
        cin >> w;
    }

    cout << backpack(W, weights) << endl;

    return 0;
}
