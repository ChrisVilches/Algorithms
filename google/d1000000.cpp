#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  cin >> N;

  vector<int> dice(N);

  for (int i = 0; i < N; i++) {
    cin >> dice[i];
  }

  sort(dice.begin(), dice.end());

  int curr = 0;

  for (int i = 0; i < N; i++) {
    if (dice[i] > curr) {
      curr++;
    }
  }

  cout << curr << endl;
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
