#include <cstddef>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

// 96234
// 14
// 1 3 9 10 11 22 66 198 594 1782 5346 16038 16039 32078 96234 

std::ostream& operator<<(std::ostream& stream, const vector<int>& vec) {
	stream << "[ ";
    for (auto v : vec) {
        stream << v << " ";
    }
	cout << "]";
	return stream;
}

struct State {
	int Steps;
	int From;
};

// за сколько шагов из State  можно добраться до key,
// используя From
using D = unordered_map<int, State>;
// constexpr int INF_POS = numeric_limits<int>::max();

void calc_impl(int x, int from, int step, D& d) {
	if (step > d[1].Steps) {
		return;
	}
	D::iterator i = d.find(x);
	if (i != d.end()) {
		if (i->second.Steps > step) {
			// cout << x << ": Replace [" << i->second.Steps << "," << i->second.From << "]"
			// 	<< " with [" << step << "," << from << "]" << endl;

			i->second.Steps = step;
			i->second.From = from;
		} else {
			return;
		}
	} else {
		d[x] = {step, from};
		// cout << x << " = [" << step << "," << from << "]" << endl;
	}

	if (x % 3 == 0) {
		calc_impl(x / 3, x, step + 1, d);
	}
	if (x % 2 == 0) {
		calc_impl(x / 2, x, step + 1, d);
	}
	calc_impl(x - 1, x , step + 1, d);

}

vector<int> calc(int x) {
	D d;
	d[1] = {x - 1, 2};
	calc_impl(x, x, 0, d);

	// cout << endl;
	// for (auto i : d) {
	// 	cout << i.first << ": [" << i.second.Steps << "," << i.second.From << "]" << endl;
	// }
	// cout << endl;

	vector<int> res;
	auto state = d[1];
	res.push_back(1);
	while (state.Steps) {
		// cout << "[" << state.Steps << "," << state.From << "]" << endl;
		res.push_back(state.From);
		state = d[state.From];
	}
	return res;
}

int main() {
	int n;
	cin >> n;

	auto r = calc(n);
	cout << r.size() - 1 << endl;
	for (auto i = r.begin(); i != r.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	return 0;
}
