#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  int slice;

  while (cin >> s >> slice) {
    const int n = s.size();

    set<int> idx;

    for (int i = 0; i < slice; i++) {
      if (s[i] == 'E') idx.emplace(i);
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
      if (!idx.empty()) {
        const int lo = *idx.begin();
        const int hi = i + slice;
        ans += hi - lo;
      }

      idx.erase(i);

      if (s[(i + slice) % n] == 'E') {
        idx.emplace(i + slice);
      }
    }

    cout << ans << endl;
  }
}
