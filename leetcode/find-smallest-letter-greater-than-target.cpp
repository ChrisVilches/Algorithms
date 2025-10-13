#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  char nextGreatestLetter(const vector<char>& letters, const char target) {
    int lo = 0;
    int hi = letters.size();

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      if (letters[mid] <= target) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    if (hi == static_cast<int>(letters.size())) {
      return letters.front();
    }

    return letters[hi];
  }
};
