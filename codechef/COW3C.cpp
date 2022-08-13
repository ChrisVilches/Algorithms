#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> events;

  for (int i = 0; i < N; i++) {
    int b, d;
    cin >> b >> d;
    events.emplace_back(b, 1);
    events.emplace_back(d + 1, -1);
  }

  ll ans = 0;

  sort(events.begin(), events.end());

  ll curr = 0;

  for (int i = 0; i < (int)events.size() - 1; i++) {
    curr += events[i].second;

    const int from = events[i].first;
    const int to = events[i + 1].first;

    ans += curr * (to - from);
    ans %= MOD;
  }

  cout << ans << endl;
}
