#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class queue {
    vector<T> Data;
private:
    size_t GetParent(size_t index) const {
        return index < 1 ? 0 : (index + 1) / 2 - 1;
    }
    size_t GetLeft(size_t index) const {
        return 2 * index + 1;
    }
    size_t GetRight(size_t index) const {
        return 2 * index + 2;
    }
public:
    void Print() const {
        cout << "[ ";
        for (auto v : Data) {
            cout << v << " ";
        }
        cout << "]" << endl;
    }

    void Insert(T v) {
        size_t pos = Data.size();
        Data.push_back(v);

        if (pos == 0) return;
        for (size_t parent = GetParent(pos);
             Data[pos] > Data[parent];
             parent=GetParent(pos)
        ) {
            swap(Data[pos], Data[parent]);
            pos = parent;
        }
    }

    T Extract(size_t position = 0) {
        // assert(!Data.empty());

        T res = Data[position];
        Data[position] = Data.back();
        Data.pop_back();

        do {
            size_t largest = position;
            size_t l = GetLeft(position);
            size_t r = GetRight(position);

            if (l < Data.size() && Data[l] > Data[largest]) {
                largest = l;
            }

            if (r < Data.size() && Data[r] > Data[largest]) {
                largest = r;
            }

            if (position == largest) {
                break;
            } else {
                swap(Data[position], Data[largest]);
                position = largest;
            } 
        } while (true);

        return res;
    }
};

const string ExtractMax = "ExtractMax";

int main() {
    int n;
    cin >> n;
    
    string s;
    queue<size_t> q;

    while (n-- >= 0)  {
        getline(cin, s);
        if (s.empty()) continue;

        // cout << "got: [" << s << "]" << endl;
        if (s == ExtractMax) {
            cout << q.Extract() << endl;
        } else {
            size_t pos = s.find(" ");
            string cmd = s.substr(0, pos);
            size_t val = std::stoi( s.substr(pos+1) );
            q.Insert(val);
        }

        // q.Print();
    }
    return 0;
}
