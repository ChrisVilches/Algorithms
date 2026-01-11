#include <bits/stdc++.h>
using namespace std;

vector<int> compute_z(const string& s) {
  const int n = s.size();
  vector<int> z(n, 0);

  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);

    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;

    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }

  return z;
}

vector<int> compute_lps(const string& s) {
  const int n = s.size();
  vector<int> lps(n);
  lps.front() = 0;
  for (int i = 1, len = 0; i < n; i++) {
    while (len != 0 && s[i] != s[len]) len = lps[len - 1];
    lps[i] = s[i] == s[len] ? ++len : 0;
  }
  return lps;
}

int main() {
  string s;
  while (cin >> s) {
    const size_t n = s.size();
    const vector<int> lps = compute_lps(s);
    const vector<int> z = compute_z(s);

    vector<int> lengths;
    for (int len = n;; len = lps[len - 1]) {
      if (len == 0) break;
      lengths.emplace_back(len);
    }

    vector<int> counts(n + 1, 0);

    for (size_t i = 1; i < n; i++) {
      counts[z[i]]++;
    }

    partial_sum(counts.rbegin(), counts.rend(), counts.rbegin());

    cout << lengths.size() << '\n';

    for (const int l : views::reverse(lengths)) {
      cout << format("{} {}\n", l, counts[l] + 1);
    }
  }
}
