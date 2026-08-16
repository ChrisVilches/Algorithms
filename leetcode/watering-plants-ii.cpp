#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumRefill(const vector<int>& plants, const int A, const int B) {
    const int n = plants.size();

    int ans = 0;

    int a = A, b = B;

    for (int i = 0, j = n - 1; i < n / 2; i++, j--) {
      if (plants[j] > b) {
        ans++;
        b = B;
      }

      if (plants[i] > a) {
        ans++;
        a = A;
      }

      a -= plants[i];
      b -= plants[j];
    }

    ans += n % 2 == 1 && plants[n / 2] > max(a, b);

    return ans;
  }
};
