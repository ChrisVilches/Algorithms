#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int carFleet(const int target, const vector<int>& position, const vector<int>& speed) {
    vector<pair<double, double>> cars;

    for (size_t i = 0; i < position.size(); i++) cars.emplace_back(position[i], speed[i]);
    sort(cars.begin(), cars.end());

    stack<double> s;

    for (const auto [pos, v] : cars) {
      const double time = (target - pos) / v;

      while (!s.empty() && s.top() <= time) s.pop();

      s.emplace(time);
    }

    return s.size();
  }
};
