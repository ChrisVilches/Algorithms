#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countCollisions(string directions) {
    const int n = directions.size();

    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
      char& a = directions[i];
      char& b = directions[i + 1];
      if (a == 'R' && b == 'L') {
        ans += 2;
        a = 'S';
        b = 'S';
        i++;
      }
    }

    for (int i = 0; i < n - 1; i++) {
      if (directions[i] != 'S') continue;

      while (i < n - 1 && directions[i + 1] == 'L') {
        ans++;
        i++;
      }
    }

    for (int i = n - 1; i > 0; i--) {
      if (directions[i] != 'S') continue;

      while (i > 0 && directions[i - 1] == 'R') {
        ans++;
        i--;
      }
    }

    return ans;
  }
};
