#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  while (cin >> s) {
    vector<int> nums;

    for (const char c : s) {
      nums.emplace_back(c == 'R' ? 1 : -1);
    }

    int ans = 1;

    pair<int, int> res{0, 0};

    for (int iter = 0; iter < 2; iter++) {
      int curr = 0;

      for (int i = 0, j = 0; j < (int)nums.size(); j++) {
        const bool neg = curr < 0;
        curr = max(curr, 0);
        curr += nums[j];

        if (curr == 1 && neg) {
          i = j;
        }

        if (curr > ans || (curr == ans && i < res.first)) {
          ans = curr;
          res = {i, j};
        }
      }

      for (int& x : nums) x = -x;
    }

    cout << res.first + 1 << ' ' << res.second + 1 << endl;
  }
}
