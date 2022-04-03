#include <bits/stdc++.h>
using namespace std;

void solve() {
  int R, C;
  cin >> R >> C;

  for (int i = 0; i < R; i++) {
    cout << (i == 0 ? "." : "+");

    for (int j = 0; j < C; j++) {
      cout << (i == 0 && j == 0 ? ".+" : "-+");
    }

    cout << endl;
    cout << (i == 0 ? "." : "|");

    for (int j = 0; j < C; j++) {
      cout << ".|";
    }

    cout << endl;
  }

  cout << "+";

  for (int j = 0; j < C; j++) {
    cout << "-+";
  }

  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ":" << endl;
    solve();
  }
}
