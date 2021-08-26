#include <cstddef>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int INF_NEG = numeric_limits<int>::min();

int solve_impl(const vector<int>& steps, vector<int>& D, int index) {
	if (index < 0)  {
		return 0;
	}

	int step1 = solve_impl(steps, D, index - 1);
	int step2 = solve_impl(steps, D, index - 2);

	return D[index] = steps[index] + max(step1, step2);
}

int solve(const vector<int>& steps) {
	vector<int> D(steps.size(), INF_NEG);
	return solve_impl(steps, D, steps.size() - 1);
}

int solve_bu(const vector<int>& steps) {
	const int N = steps.size();
	vector<int> D(N + 2, 0);

	for (int i = 0; i < N; ++i) {
		D[i+2] = max(D[i + 2 - 1], D[i + 2 - 2]) + steps[i];
	}

	return D.back();
}

int main() {
	int N;
	cin >> N;
	vector<int> steps(N);
	for (int& s : steps) {
		cin >> s;
	}
	cout << solve_bu(steps) << endl;
	return 0;
}
