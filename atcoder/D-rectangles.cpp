#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  map<int, vector<int>> by_x;

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    by_x[x].emplace_back(y);
  }

  for (auto& [_, v] : by_x) {
    sort(v.begin(), v.end());
  }

  int ans = 0;

  unordered_map<long long, int> count;

  for (const auto& [_, v] : by_x) {
    const int size = v.size();

    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        const long long key = v[i] + (static_cast<long long>(v[j]) << 32);
        ans += count[key];
        count[key]++;
      }
    }
  }

  cout << ans << endl;
}
