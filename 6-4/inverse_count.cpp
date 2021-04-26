#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;
using T = unsigned long long;
using V = vector<T>;

void print(const V& vec) {
    for (auto v: vec) {
        cout << v << " ";
    }
    cout << endl;
}

int n2(const V& vec) {
    int res = 0;
    for (int i = 0; i < vec.size() - 1; ++i) {
        for (int j = i + 1; j < vec.size(); ++j) {
            if (i < j && vec[i] > vec[j]) {
                res++;
            }
        }
    }
    return res;
}

V merge(const V& l, const V& r, size_t& res) {
    V m;
    int li = 0, ri = 0;
    while (li < l.size() && ri < r.size()) {
        if (l[li] <= r[ri]) {
            m.push_back(l[li++]);
        } else {
            res += l.size() - li;
            m.push_back(r[ri++]);
        }
    }
    while (ri < r.size()) {
        m.push_back(r[ri++]);
    }
    while (li < l.size()) {
        m.push_back(l[li++]);
    }
    return m;
}

size_t rec(V& vec) {
    if (vec.size() < 2) {
        return 0;
    }
    // cout << "IN: "; print(vec);

    size_t m = vec.size() / 2;
    size_t res = 0;
    V l(m);
    size_t i = 0;
    for (; i < m; ++i) l[i] = vec[i];
    res += rec(l);

    V r(vec.size() - m);
    for (; i < vec.size(); ++i) r[i - m] = vec[i];
    res += rec(r);

    vec = merge(l, r, res);
    // cout << "sorted: "; print(vec);
    // cout << " res: " << res << endl;
    return res;
}

int main() {
    size_t N;
    cin >> N;
    V vec;
    T val;
    for (size_t i = 0; i < N; ++i) {
        cin >> val;
        vec.emplace_back(val);
    }
    // cout << "N^2 " << n2(vec) << endl;
    cout << rec(vec) << endl;
    return 0;
}
