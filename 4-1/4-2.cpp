#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Item final {
    int value;
    int weight;
};

double get_max_knapsack_value(int capacity, std::vector<Item> items) {
    double value = 0.0;

    sort(items.begin(), items.end(), [](const Item& l, const Item& r) {
        return (double(l.value) / l.weight) > (double(r.value) / r.weight);
    });

    // take items while there is empty space in knapsack
    for (auto &item: items) {
        // cout << "capacity: " << capacity << " item: " << item.value << "$ " << item.weight << "kg" << endl;
        if (capacity > item.weight) {
            // can take full item and continue
            capacity -= item.weight;
            value += item.value;
        } else {
            value += item.value * (static_cast<double>(capacity) / item.weight);
            break;
        }
    }

    return value;
}

bool equals(double test, double res) {
    if (abs(test - res) > 0.001) {
        cout << test << " != " << res << endl;
        return false;
    }
    return true;
}

int main(void) {
    // assert(equals(180, get_max_knapsack_value(50, {{60,20}, {100, 50}, {120, 30}})));
    // return 0;

    int number_of_items;
    int knapsack_capacity;
    std::cin >> number_of_items >> knapsack_capacity;
    std::vector<Item> items(number_of_items);
    for (int i = 0; i < number_of_items; i++) {
        std::cin >> items[i].value >> items[i].weight;
    }

    double max_knapsack_value = get_max_knapsack_value(knapsack_capacity, std::move(items));

    std::cout.precision(10);
    std::cout << max_knapsack_value << std::endl;
    return 0;
}
