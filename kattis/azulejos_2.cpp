#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

map<int, set<pii>> read(const int n) {
  vector<pii> vec(n);
  for (pii& elem : vec) cin >> elem.first;
  for (pii& elem : vec) cin >> elem.second;

  map<int, set<pii>> res;
  for (int i = 0; i < n; i++) {
    res[vec[i].first].emplace(vec[i].second, i);
  }

  return res;
}

void solve(const int n) {
  auto back_all = read(n);
  auto front_all = read(n);

  vector<pii> res;

  while (!back_all.empty()) {
    auto& back = back_all.begin()->second;
    auto& front = front_all.begin()->second;

    if (back.size() >= front.size()) {
      const auto [h, front_idx] = *front.begin();
      front.erase(front.begin());
      const auto it = back.lower_bound({h + 1, -1});

      if (it == back.end()) break;
      const auto [_, back_idx] = *it;
      res.emplace_back(back_idx, front_idx);
      back.erase(it);
    } else {
      const auto [h, back_idx] = *back.begin();
      back.erase(back.begin());
      auto it = front.lower_bound({h, -1});

      if (it == front.begin()) break;
      it--;
      const auto [_, front_idx] = *it;
      res.emplace_back(back_idx, front_idx);
      front.erase(it);
    }

    if (back.empty()) back_all.erase(back_all.begin());
    if (front.empty()) front_all.erase(front_all.begin());
  }

  if (n != (int)res.size()) {
    cout << "impossible" << endl;
    return;
  }

  for (const auto& [x, _] : res) cout << x + 1 << " ";
  cout << endl;
  for (const auto& [_, x] : res) cout << x + 1 << " ";
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while (cin >> n) solve(n);
}
