#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int L, C, N;
int P, X;
ll A, B;
set<pii> ranges;

int range_color_count(set<pii>::iterator it) {
  auto [from, color] = *it;
  int to = next(it) == ranges.end() ? L : next(it)->first;
  return to - from;
}

int count_color(const int c) {
  int total = 0;

  for (auto it = ranges.begin(); it != ranges.end(); it++) {
    auto [_, color] = *it;
    int length = range_color_count(it);
    if (color == c) total += length;
  }

  return total;
}

void execute_step() {
  const ll S = count_color(P);
  const int m1 = (A + S * S) % L;
  const int m2 = (A + (S + B) * (S + B)) % L;

  const int interval_from = min(m1, m2);
  const int interval_to = max(m1, m2);

  int prev_color;

  auto prev_it = ranges.lower_bound({interval_from, -1});
  if (prev_it != ranges.begin()) prev_it = prev(prev_it);
  prev_color = prev_it->second;

  while (true) {
    auto it = ranges.lower_bound({interval_from, -1});
    if (it == ranges.end() || interval_to < it->first) break;
    prev_color = it->second;
    ranges.erase(it);
  }

  ranges.insert({interval_from, X});

  auto next_it = ranges.lower_bound({interval_to + 1, -1});
  if (next_it->first != interval_to + 1) ranges.insert({interval_to + 1, prev_color});
}

void solve() {
  ranges = set<pii>{{0, 1}};

  for (int i = 0; i < N; i++) {
    cin >> P >> X >> A >> B;
    execute_step();
  }

  map<int, int> counts;
  int ans = 0;

  for (auto it = ranges.begin(); it != ranges.end(); it++) {
    counts[it->second] += range_color_count(it);
    ans = max(ans, counts[it->second]);
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> L >> C >> N) solve();
}
