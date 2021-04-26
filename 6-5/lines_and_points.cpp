#include <iostream>
#include <list>
#include <memory>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


struct RangeTree {

    struct Range {
        int Left, Right;
    };

    struct Node {
        int MinLeft, MaxRight;
        shared_ptr<Node> Left, Right;
        list<Range> Items;

        Node(int left, int right)
            : MinLeft(left), MaxRight(right)
        {
            assert(left < right);
        }

        int Center() const {
            return MinLeft + (Length() / 2);
        }

        int Length() const {
            return MaxRight - MinLeft;
        }
    };

    Node Root;
    RangeTree(int minLeft, int maxRight)
        :Root(minLeft, maxRight)
    {
    }

    void Add(int left, int right) {
        Node* node = &Root;

        int depth = -1;
        while (node->Length() > 1) {
            int center = node->Center();
            ++depth;
            if (left > center) {
                if (!node->Right) {
                    node->Right = make_shared<Node>(center, node->MaxRight);
                }
                node = node->Right.get();
            } else if (right < center) {
                if (!node->Left) {
                    node->Left = make_shared<Node>(node->MinLeft, center);
                }
                node = node->Left.get();
            } else 
                break;
        }

        node->Items.push_back({left, right});
        // cout << depth << ": [" << node->MinLeft << "," << node->MaxRight << "] add {" << range.Left << "," << range.Right << "}" << endl;
    }

    int GetIntersectCount(int x) const {
        int res = 0;
        const Node* node = &Root;

        int depth = -1;
        while (node != nullptr) {
            ++depth;
            for (auto& r : node->Items) {
                if (r.Left <= x && x <= r.Right) {
                    ++res;
                    // cout << endl << x << " in " << r.Left << ":" << r.Right << " = " << res << endl;
                }
            }
            if (x < node->Center()) {
                node = node->Left.get();
            } else {
                node = node->Right.get();
            }
        }
        return res;
    }

};


struct OverlapTree {
    struct Point {
        int In, Over, Out;
    };
    using Map = map<int, Point>;
    Map X;

    void print() const {
        cout << "0";
        for (auto i : X) {
            cout << " -> [" << i.first << ":" << i.second.In << "/" << i.second.Over << "/" << i.second.Out << "]";
        }
        cout << " -> 0" << endl;
    }

    int GetPrevOver(Map::iterator i) const {
        if (i == X.begin()) return 0;
        auto& p = std::prev(i)->second;
        return p.Over + p.Out;
    }

    OverlapTree& Add(int left, int right) {
        // cout << "Add [" << left << "," << right << "]: ";

        auto r = X.lower_bound(right);
        if (r == X.end()) {
            X[right] = {0, 0, 0};
        } else if (r->first > right) {
            X[right] = {0, GetPrevOver(r), 0};
        }

        if (left == right) {
           X[left].In++;
           return *this;
        }

        auto i = X.lower_bound(left);
        if (i == X.end()) {
            X[left] = {0, 0, 1};
        } else if (i->first > left) {
            X[left] = {0, GetPrevOver(i), 1};
        }

        while (i != X.end()) {
            if (i->first == left) {
                i->second.Out++;
            } else if (i->first < right)  {
                i->second.Over++;
            } else if (i->first == right) {
                i->second.In++;
                break;
            } 
            ++i;
        }
        // print();
        return *this;
    }

    int GetIntersectCount(int x) {
        if (x < X.begin()->first) {
            return 0;
        }
        auto i = X.lower_bound(x);
        if (i == X.end()) {
            return 0;
        }
        if (i == X.begin() || i->first == x) {
            return i->second.In + i->second.Over + i->second.Out;
        }
        auto p = std::prev(i);
        // cout << "i: " << i->first << "," << i->second
        //      << " p: " << p->first << "," << p->second << endl;

        return p->second.Over + p->second.Out;
    }
};

struct Sort2 {
    // multimap<int, int> Begins, Ends;
    vector<int> Begins, Ends;
    bool IsSorted = false;

    Sort2& Add(int left, int right) {
        // Begins.emplace(left, right);
        // Ends.emplace(right, left);
        IsSorted = false;
        Begins.push_back(left);
        Ends.push_back(right);
        return *this;
    }

    void Sort() {
        sort(Begins.begin(), Begins.end());
        sort(Ends.begin(), Ends.end());
    }

    int GetIntersectCount(int x) {
        if (!IsSorted) {
            Sort();
            IsSorted = true;
        }
        // cout << endl << "X: " << x << endl;

        // кол-во подходящих отрезков, с левой границей <= x
        // for (auto i : Begins) {
        //     cout << "[" << i.first << "," << i.second << "] ";
        // }

        auto b = upper_bound(Begins.begin(), Begins.end(), x);
        int bc = 0;
        if (b != Begins.end()) {
            bc = distance(Begins.begin(), b);
            // cout << " found: " << b->first;
        } else {
            if (*prev(b) <= x) {
                bc = Begins.size();
            }
        }
        // cout << " count: " << bc << endl;

        // for (auto i : Ends) {
        //     cout << "[" << i.second << "," << i.first << "] ";
        // }

        // кол-во НЕ подходящих отрезков c правой границей < x
        auto e = upper_bound(Ends.begin(), Ends.end(), x - 1);
        int ec = 0;
        if (e != Ends.end()) {
            ec = distance(Ends.begin(), e);
            // cout << " found: " << e->first;
        } else {
            if (*prev(e) < x) {
                ec = Ends.size();
            }
        }
        // cout << " count: " << ec << endl;

        return abs(bc - ec);
    }
};

template <class T>
bool test(T& tree, const vector<int>& tests, const vector<int>& answers) {
    assert(tests.size() == answers.size());
    for (size_t i = 0; i < tests.size(); ++i) {
        int res = tree.GetIntersectCount(tests[i]);
        if (res != answers[i]) {
            cerr << "Bad answer [" << i << "], check " << tests[i] << " wants: " << answers[i] << " got " << res << endl;
            return false;
        }
    }
    return true;
}

template <class T>
void tests() {
    {
        T tree;
        tree.Add(0,5).Add(7, 10);
        assert(test(tree, {1, 6, 11}, {1, 0, 0}));
    }
    {
        T tree;
        tree.Add(0,3).Add(1,3).Add(2, 3).Add(3, 4).Add(3, 5).Add(3, 6);
        assert(test(tree, {1, 2, 3, 4, 5, 6}, {2, 3, 6, 3, 2, 1}));
    }
    {
        T tree;
        tree.Add(0,4).Add(1, 5).Add(2, 6);
        assert(test(tree, {-1, 0, 1, 2, 3, 4, 5, 6, 7}, {0, 1, 2, 3, 3, 3, 2, 1, 0}));
    }
    {
        T tree;
        tree.Add(-2, 3).Add(0, 3).Add(-1, 0).Add(-1, 3).Add(0, 1)
            .Add(-2, -1).Add(1, 3).Add(2, 3).Add(1, 2).Add(2, 3);
        assert(test(tree, {-3, -1, 0, 1, 2, 3}, {0, 4, 5, 6, 7, 6}));
    }
    {
        T tree;
        tree.Add(0, 0).Add(-1, 1).Add(-2, 2).Add(-3, 3).Add(-4, 4).Add(-5, 5);
        assert(test(tree, {-5, -4, -3, -1, 0, 1, 3, 4, 5}, {1, 2, 3, 5, 6, 5, 3, 2, 1}));
    }
    {
        T tree;
        tree.Add(6, 6).Add(2, 3).Add(2, 5).Add(3, 5).Add(2, 7).Add(5, 7).Add(3, 7);
        assert(test(tree, {1, 2, 3, 5, 6, 7}, {0, 3, 5, 5, 4, 3}));
    }
    {
        T tree;
        tree.Add(-1, -1).Add(0, 1).Add(-1,-1).Add(-1, -1);
        assert(test(tree, {-2, -1, 0, 1, 2}, {0, 3, 1, 1, 0}));
    }
}

#include <ctime>
int Random(int min, int max) {
  return min + rand() % (max - min);
}

void brute() {
    const int MAX = 20;
    const int LINES = 5000;
    while (1) {
        int N = Random(1, LINES);

        RangeTree RTree(-MAX, MAX);
        OverlapTree OTree;
        vector<pair<int, int>> lines;
        int ml = MAX;
        int mr = -MAX;
        for (int i = 0; i < N; i++) {
            int l = Random(-MAX, MAX);
            int r = Random(-MAX, MAX);
            if (r < l) {
                swap(r, l);
            }
            ml = min(ml, l);
            mr = max(mr, r);
            lines.emplace_back(l, r);
            RTree.Add(l, r);
            OTree.Add(l, r);
        }

        cout << N << ": (" << ml << "," << mr << ") ";
        cout.flush();

        for (int x = ml - 1; x <= mr + 1; ++x) {
            int r = RTree.GetIntersectCount(x);
            int o = OTree.GetIntersectCount(x);
            if (r != o) {
                cout << endl << "x: " << x << " Rtree " << r << " vs " << o << " OTree" << endl;
                
                cout << N << " " << 1 << endl;
                for (auto l : lines) {
                    cout << l.first << " " << l.second << endl;
                }
                cout << x << endl;
                cout << endl;
                return;
            }
        }
    }
}

int main() {
    if (0) {
        tests<Sort2>();
        // brute();
        return 0;
    }
    int N, M, x;
    cin >> N;
    cin >> M;

    // const int MAX = 1000000000;
    // RangeTree tree(-MAX, MAX);
    // OverlapTree tree;
    Sort2 tree;
    tree.Begins.resize(N);
    tree.Ends.resize(N);

    // int l, r;
    for (int i = 0; i < N; ++i) {
        cin >> tree.Begins[i]; 
        cin >> tree.Ends[i];
        // tree.Add(l, r);
    }
    // tree.print();

    for (int i = 0; i < M; ++i) {
        cin >> x;
        // cout << endl << "[" << x << "]:";
        cout << tree.GetIntersectCount(x) << " ";
    }
    cout << endl;
    return 0;
}
