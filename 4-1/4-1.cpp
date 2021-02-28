#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct AB {
    int A, B;
};


struct Cmp {
    bool operator()( const AB& lhs, const AB& rhs ) const {
        if (lhs.B < rhs.B) {
            return true;
        } else if (lhs.B == rhs.B) {
            return lhs.A <= rhs.A; 
        }
        return false;
    }
};

vector<int> get_covering_set(vector<AB> segments) {
    vector<int> result;

    set<AB, Cmp> ABs(segments.begin(), segments.end());
    // assert(segments.size() == ABs.size());

    while (ABs.size() > 0) {
        auto i = ABs.begin();
        const AB& seg = *i;

        // cout << "take [" << i->A << "," << i->B << "]" << endl; 
        result.push_back(seg.B);
        while (i != ABs.end() && i->A <= seg.B) {
            // cout << "erase: [" << i->A << "," << i->B << "]" << endl;
            i = ABs.erase(i);
        }
    }

    return result;
}

bool equals(const vector<int>& l, const vector<int>& r) {
    if (l.size() != r.size()) {
        cerr << l.size() << " != " << r.size() << " ";
        for (auto i: l) cout << i << " ";
        cout << " Vs ";
        for (auto i: r) cout << i << " ";
        return false;
    }
    for (size_t i = 0; i < l.size(); ++i) {
        if (l[i] != r[i]) {
            cerr << l[i] << " != " << r[i] << endl;
            return false;
        }
    }
    return true;
}

int main(void) {
    // assert(equals({3}, get_covering_set({{1, 3}, {2, 5}, {3, 6}})));
    // assert(equals({3, 6}, get_covering_set({{4,7}, {1,3}, {2,5}, {5,6}})));
    // assert(equals({3, 5, 9}, get_covering_set({{2,3}, {1,4}, {4,5}, {3,7}, {2, 7}, {2, 8}, {4, 9}, {7, 9}})));
    // return 0;

    int segments_count;
    cin >> segments_count;
    vector<AB> segments(segments_count);
    for (auto &s: segments) {
        cin >> s.A >> s.B;
    }

    auto points = get_covering_set(move(segments));
    cout << points.size() << endl;
    for (auto point : points) {
        cout << point << " ";
    }
    cout << endl;
    return 0;
}
