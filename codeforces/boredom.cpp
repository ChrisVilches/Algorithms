#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX 100001

int N;
ll memo[MAX], values[MAX], freq[MAX];

ll dp(const int i) {
  if (i >= N) return 0;
  if (~memo[i]) return memo[i];

  ll take = values[i] * freq[i];
  take += (values[i + 1] == values[i] + 1) ? dp(i + 2) : dp(i + 1);

  ll skip = dp(i + 1);

  return memo[i] = max(take, skip);
}

int main() {
  memset(memo, -1, sizeof memo);
  cin >> N;

  map<int, int> counts;

  for (int i = 0; i < N; i++) {
    int n;
    cin >> n;
    counts[n]++;
  }

  int idx = 0;

  for (auto it = counts.begin(); it != counts.end(); it++) {
    values[idx] = it->first;
    freq[idx] = it->second;

    idx++;
  }

  cout << dp(0) << endl;
}
