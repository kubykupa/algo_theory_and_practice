#include <iostream>
#include <vector>

using namespace std;

// 0  1 2   3  4  5 6   7  8  9 10 11
// 3,20,4, 30,21,30,5, 31,60,30,21,31

int isHeap(const vector<int>& v) {
    size_t min_count = 0;
    size_t max_count = 0;
    size_t j = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            j = (i+1)/2 - 1;
            // cout << "[" << i << "] " << v[i] << " under parent [" << j << "] " << v[j] << endl;
            if (v[i] < v[j]) {
                max_count++;
            }

            if (v[i] > v[j]) {
                min_count++;
            }
        }

        j = 2 * i + 1;
        if (j >= v.size()) continue;
        if (v[i] > v[j]) {
            max_count++;
        }
        if (v[i] < v[j]) {
            min_count++;
        }

        j += 1;
        if (j >= v.size()) continue;
        if (v[i] > v[j]) {
            max_count++;
        }
        if (v[i] < v[j]) {
            min_count++;
        }
    }

    cout << min_count << " " << max_count << endl;
    if (max_count == 0) {
        return -1;
    }
    if (min_count == 0) {
        return 1;
    }
    return 0;
}

int main() {
    assert(isHeap({10,14,11}) == -1);
    assert(isHeap({2,4,5,12,5,6}) == -1);
    assert(isHeap({8, -3,2, -4,-4, 1,-10}) == 1);
    assert(isHeap({3,-2,-1}) == 1);
    return 0;
}
