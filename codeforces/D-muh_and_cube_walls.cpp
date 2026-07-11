#include <bits/stdc++.h>
using namespace std;

vector<int> compute_lps(const vector<int>& pattern) {
  const int n = pattern.size();
  vector<int> lps(n);
  lps.front() = 0;
  for (int i = 1, len = 0; i < n; i++) {
    while (len != 0 && pattern[i] != pattern[len]) len = lps[len - 1];
    if (pattern[i] == pattern[len]) len++;
    lps[i] = len;
  }
  return lps;
}

int main() {
  int n, w;
  while (cin >> n >> w) {
    vector<int> all(n), pattern(w);
    for (int& x : all) cin >> x;
    for (int& x : pattern) cin >> x;

    if (w > n) {
      cout << 0 << endl;
      continue;
    } else if (w == 1) {
      cout << n << endl;
      continue;
    }

    for (int i = 0; i < n - 1; i++) all[i] -= all[i + 1];
    for (int i = 0; i < w - 1; i++) pattern[i] -= pattern[i + 1];

    all.resize(n - 1);
    pattern.resize(w - 1);

    const vector<int> lps = compute_lps(pattern);

    int ans = 0;

    for (size_t i = 0, j = 0; i < all.size();) {
      if (pattern[j] == all[i]) {
        j++;
        i++;
      }

      if (j == pattern.size()) {
        ans++;
        j = lps[j - 1];
      } else if (i < all.size() && pattern[j] != all[i]) {
        if (j != 0)
          j = lps[j - 1];
        else
          i++;
      }
    }

    cout << ans << endl;
  }
}
