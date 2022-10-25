#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> arr;
  vector<int> memo;
  int d;
  int st[1001][11];

  int max_query(int L, int R) const {
    const int k = 31 - __builtin_clz(R - L + 1);
    return max(st[L][k], st[R - (1 << k) + 1][k]);
  }

  bool can_jump(const int from, const int to) const {
    if (to < 0 || to >= (int)arr.size()) return false;
    if (arr[from] <= arr[to]) return false;
    if (abs(from - to) == 1) return true;

    const int highest = max_query(min(from, to) + 1, max(from, to) - 1);

    return highest < arr[from];
  }

  int dp(const int i) {
    if (~memo[i]) return memo[i];

    int max_value = 0;

    for (int j = i - d; j <= i + d; j++) {
      if (!can_jump(i, j)) continue;
      max_value = max(max_value, dp(j));
    }

    return memo[i] = 1 + max_value;
  }

  void build_table() {
    const int N = arr.size();

    const int size = ceil(log2(N));

    for (int i = 0; i < N; i++) st[i][0] = arr[i];

    for (int k = 1; k < size; k++)
      for (int i = 0; i + (1 << k) <= N; i++)
        st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
  }

 public:
  int maxJumps(vector<int>& arr, int d) {
    this->arr = arr;
    this->d = d;
    build_table();
    memo.assign(arr.size(), -1);

    int ans = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
      ans = max(ans, dp(i));
    }

    return ans;
  }
};
