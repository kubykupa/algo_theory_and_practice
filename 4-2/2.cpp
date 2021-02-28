#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <list>

using namespace std;

struct Node {
    char Value = 0;
    Node* Zero = nullptr; //  Left child
    Node* One = nullptr;  // Right child

    ~Node() {
        if (Zero) {
            delete Zero;
        }
        if (One) {
            delete One;
        }
    }

    Node* GetZero() {
        if (Zero == nullptr) {
            // cout << "[<]";
            Zero = new Node();
        } else {
            // cout << ">";
        }
        return Zero;
    }
    Node* GetOne() {
        if (One == nullptr) {
            // cout << "[>]";
            One = new Node();
        } else {
            // cout << ">";
        }
        return One;
    }
};

constexpr char ZERO = '0';

int main() {
    string s;
    getline(cin, s);

    size_t pos = s.find(" ");
    size_t k = std::stoi( s.substr(0, pos) );
    size_t l = std::stoi( s.substr(pos+1) );

    // cout << "k: " << k << " l: " << l << endl;

    unordered_map<char, string> char2code;
    for (size_t i = 0; i < k; ++i) {
        getline(cin, s);
        char2code[s[0]] = s.substr(3);
    }

    getline(cin, s);
    // cout << "encoded: " << s << endl;

    Node root;
    for (auto i : char2code) {
        // cout << "build tree: " << i.first << " " << i.second << endl;

        Node* n = &root;
        for (char c : i.second) {
            // cout << "(" << c << ")";
            if (c == ZERO) {
                n = n->GetZero();
            } else {
                n = n->GetOne();
            }
        }
        // cout << " [ " << i.first << " ]" << endl;
        n->Value = i.first;
    }

    Node* n = &root;
    for (char c : s) {
        if (c == ZERO) {
            // assert(n->Zero != nullptr);
            n = n->Zero;
        } else {
            // assert(n->One != nullptr);
            n = n->One;
        }
        if (n->Zero == nullptr && n->One == nullptr) {
            cout << n->Value; 
            n = &root;
        }
    }
    cout << endl;

    return 0;
}
