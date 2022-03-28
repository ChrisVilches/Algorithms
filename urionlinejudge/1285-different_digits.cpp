#include <bits/stdc++.h>
using namespace std;

bool has_repeated(const int n) {
  string s = to_string(n);
  unordered_map<int, int> freq;

  for (char c : s) {
    freq[c]++;
    if (freq[c] != 1) return true;
  }

  return false;
}

void count(const int N, const int M) {
  int ans = 0;

  for (int i = N; i <= M; i++) {
    ans += !has_repeated(i);
  }

  cout << ans << endl;
}

int main() {
  int N, M;

  while (cin >> N >> M) {
    if (N > M) swap(N, M);
    count(N, M);
  }
}
