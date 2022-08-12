#include <bits/stdc++.h>
using namespace std;

int count_leading_zeros(int n) {
  int ret = 0;
  while ((n & (1 << 31)) == 0) {
    n <<= 1;
    ret++;
  }
  return ret;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;

    vector<int> leading_zeros(32, 0);

    for (int i = 0; i < N; i++) {
      int a;
      cin >> a;
      leading_zeros[count_leading_zeros(a)]++;
    }

    long long ans = 0;

    for (const long long lz : leading_zeros) {
      ans += (lz * (lz - 1) / 2);
    }

    cout << ans << endl;
  }
}
