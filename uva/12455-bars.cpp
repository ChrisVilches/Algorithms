#include <bits/stdc++.h>
using namespace std;

bool solve() {
  int N, p;
  cin >> N >> p;

  vector<int> nums(p);

  for (int i = 0; i < p; i++) {
    cin >> nums[i];
  }

  for (int i = 0; i < (1 << p); i++) {
    int total = 0;

    for (int j = 0; j < p; j++) {
      if ((i & (1 << j)) == 0) continue;

      total += nums[j];
    }

    if (total == N) return true;
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    if (solve()) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
