#include <iostream>
#include <vector>

using namespace std;

vector<int> split(int N) {
    vector<int> result;
    if (N <= 2) return {N};

    int i = 1;
    while (N > 0) {
        if (N - i >= 0) {
            N -= i;
            if (N <= i) {
                result.push_back(N + i);
                break;
            } else {
                result.push_back(i++);
            }
        } else {
            result.push_back(N);
            break;
        }
    }
    return result;
}

int main() {
    int N;
    cin >> N;
    auto res = split(N);
    cout << res.size() << endl;
    for (auto i : res) {
        cout << i << " ";
    }
    return 0;
}
