#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  cin >> N;

  deque<int> d;

  for (int i = 0; i < N; i++) {
    int v;
    cin >> v;
    d.push_back(v);
  }

  int curr = 0;
  int ans = 0;

  for (int i = 0; i < N; i++) {
    int v;
    if (d.back() > d.front()) {
      v = d.front();
      d.pop_front();
    } else {
      v = d.back();
      d.pop_back();
    }

    if (v >= curr) {
      ans++;
      curr = v;
    }
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
