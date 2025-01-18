#include <bits/stdc++.h>
using namespace std;

int main() {
  int s, n;

  while (cin >> s >> n) {
    vector<bool> visited(s, false);

    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      visited[x - 1] = true;
    }

    int ans = 0;

    for (int i = 0; i < s; i++) {
      const bool prev = !visited[(i - 1 + s) % s];
      const bool curr = !visited[i];
      const bool next = !visited[(i + 1) % s];

      if (prev && curr && next) {
        visited[i] = true;
        ans++;
      }
    }

    cout << ans << endl;
  }
}
