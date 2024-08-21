#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, c;
  vector<tuple<int, int, int>> values;
  unordered_map<int, int> freqs;
  unordered_map<int, int> first_index;

  cin >> n >> c;

  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;

    freqs[val]++;

    if (!first_index.count(val)) {
      first_index[val] = i;
    }
  }

  for (const auto [x, freq] : freqs) {
    values.emplace_back(freq, -first_index[x], x);
  }

  sort(values.rbegin(), values.rend());

  for (const auto& [f, _, x] : values) {
    for (int i = 0; i < f; i++) {
      cout << x << ' ';
    }
  }

  cout << endl;
}
