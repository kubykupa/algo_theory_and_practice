#include <math.h>
#include <functional>
#include <map>
#include <string>
#include <iostream>


using namespace std;

double lg(double b, double a) {
    return log(b) / log(a);
}

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main() {
    map<double, string> res;

    double n = 20;
    cin >> n;

    res[pow(lg(n, 4), 0.5)] = "#1 pow(lg(n, 4), 0.5)";
    res[log2(log2(n))] = "#2 log2(log2(n))";
    res[lg(n, 3)] = "#3 lg(n,3)";
    res[pow(log2(n), 2)] = "#4 pow(log2(n), 2)";
    res[sqrt(n)] = "#5 sqrt(n)";
    res[n/lg(n, 5)] = "#6 n/lg(n, 5)";
    res[log2(factorial(n))] = "#7 log2(n!)";
    res[pow(3, log2(n))] = "#8 pow(3, log2(n))";
    res[pow(n, 2)] = "#9 pow(n, 2)";
    res[pow(7, log2(n))] = "#10 pow(7, log2(n))";
    res[pow(log2(n), log2(n))] = "#11 pow(log2(n), log2(n))";
    res[pow(n, log2(n))] = "#12 pow(n, log2(n))";
    res[pow(n, sqrt(n))] = "#13 pow(n, sqrt(n))";
    res[pow(2, n)] = "#14 pow(2, n)";
    res[pow(4, n)] = "#15 pow(4, n)";
    res[pow(2, 3 * n)] = "#16 pow(2, 3*n)";
    res[factorial(n)] = "#17 n!";
    res[pow(2, pow(2, n))] = "#18 pow(2, pow(2, n))";


    for (auto& [k, v]: res) {
        cout << v << ": " << k << endl;
    }

    return 0;
}
