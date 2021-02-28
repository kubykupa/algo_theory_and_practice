#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <list>

using namespace std;

struct Item {
    size_t Frequency;
    char Symbol;

    Item(size_t frequency, char symbol = 0)
        : Frequency(frequency)
        , Symbol(symbol)
    {}
};

struct Node {
    Item Value;
    Node* Zero = nullptr; //  Left child
    Node* One = nullptr;  // Right child

    Node(const Item& item):Value(item){}
    Node(size_t frequency, Node* zero, Node* one)
        : Value(frequency)
        , Zero(zero)
        , One(one)
    {}

    ~Node() {
        if (Zero) {
            delete Zero;
        }
        if (One) {
            delete One;
        }
    }
};

struct Cmp {
    bool operator()(Node* left, Node* right) const {
        // return left->Value.Frequency > right->Value.Frequency;
        if (left->Value.Frequency > right->Value.Frequency)
            return true;
        else if (left->Value.Frequency == right->Value.Frequency) {
            return left->Value.Symbol > right->Value.Symbol;
        }
        return false;
    }
};

using PQ = priority_queue<Node*, vector<Node*>, Cmp>;


bool pathInTree(Node* node, char c, string& path) {
    if (node->Value.Symbol == c) {
        return true;
    }

    path += '0';
    if (node->Zero != nullptr && pathInTree(node->Zero, c, path)) {   
        return true;
    }

    path.back() = '1';
    if (node->One != nullptr && pathInTree(node->One, c, path)) {   
        return true;
    }

    path.resize(path.length() - 1);

    return false;
}

string path(Node* node, char c) {
    string s;
    bool res = pathInTree(node, c, s);
    // assert(res);
    if (s.length() == 0) {
        s = "0";
    }
    return s;
}

template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while(!q.empty()) {
        Node* n = q.top();
        std::cout << "[" << n->Value.Symbol << ":" << n->Value.Frequency << "] ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    string str;
    cin >> str;
    // if (str.empty()) return 0;

    // str = "abacabad";
    // str = "beep boop beer!";
    // cout << "Str: " << str << endl;

    map<char, size_t> frequencies;
    for (char c : str) {
        frequencies[c]++;
    }

    PQ pq;
    for (auto i: frequencies) {
        // cout << i.first << ": " << i.second << endl;
        pq.push(new Node(Item(i.second, i.first)));
    }

    // print_queue(pq);

    Node *left = nullptr;

    while (!pq.empty()) {
        // cout << "--------------" << endl;
        // print_queue(pq);
        left = pq.top(); pq.pop();

        if (pq.empty()) break;

        Node* right = pq.top(); pq.pop();
        // print_queue(pq);

        Node* top = new Node(left->Value.Frequency + right->Value.Frequency, left, right);
        // cout << "L[" << left->Value.Symbol << ":" << left->Value.Frequency << "] "
        //      << "R[" << right->Value.Symbol << ":" << right->Value.Frequency << "] "
        //      << "T[" << top->Value.Frequency << "]" << endl;

        pq.push(top);
    }
    // assert(left != nullptr);
    // cout << "L: [" << left->Value.Symbol << "] " << left->Value.Frequency << endl;

    unordered_map<char, string> cache;

    string encoded;
    for (char c : str) {
        auto i = cache.find(c);
        if (i != cache.end()) {
            encoded += i->second;
            continue;
        }
        string s = path(left, c);
        cache[c] = s;
        encoded += s;
    }

    // print result
    cout << cache.size() << " " << encoded.length() << endl;
    for (auto i : cache) {
        cout << i.first << ": " << i.second << endl;
    }
    cout << encoded << endl;

    delete left;
    return 0;
}
