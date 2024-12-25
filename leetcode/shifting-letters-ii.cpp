#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string shiftingLetters(const string s, const vector<vector<int>>& shifts) {
    vector<int> deltas(s.size() + 1, 0);

    for (const auto& vec : shifts) {
      const int d = vec[2] == 1 ? 1 : -1;

      deltas[vec[0]] += d;
      deltas[vec[1] + 1] -= d;
    }

    const int n = s.size();

    int curr = 0;
    string res = s;

    for (int i = 0; i < n; i++) {
      curr += deltas[i];

      int c = res[i] - 'a' + curr;
      while (c < 0) c += 26;
      res[i] = 'a' + (c % 26);
    }

    return res;
  }
};
