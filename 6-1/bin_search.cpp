#include <iostream>
#include <vector>

using namespace std;

int bin_search(const vector<int>& vec, int x) {
    int l = 0; 
    int r = vec.size() - 1;

    int m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (vec[m] == x) {
            return m + 1;
        }
        if (vec[m] < x) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

int main() {
    int N;
    cin >> N;
    
    vector<int> vec(N);
    for (int i = 0; i < N; ++i) {
        cin >> vec[i];
    }

    int K;
    cin >> K;
    int x;
    for (int i = 0; i < K; ++i) {
        cin >> x;
        cout << bin_search(vec, x) << " ";
    }
    cout << endl;
    return 0;
}
