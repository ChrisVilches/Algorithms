#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximizeSquareArea(const int m, const int n, vector<int>& h_fences,
                         vector<int>& v_fences) {
    h_fences.emplace_back(1);
    v_fences.emplace_back(1);
    h_fences.emplace_back(m);
    v_fences.emplace_back(n);

    sort(h_fences.begin(), h_fences.end());
    sort(v_fences.begin(), v_fences.end());

    unordered_set<int> h_dist;

    for (size_t i = 0; i < h_fences.size(); i++) {
      for (size_t j = i + 1; j < h_fences.size(); j++) {
        h_dist.emplace(h_fences[j] - h_fences[i]);
      }
    }

    long long area = 0;

    for (size_t i = 0; i < v_fences.size(); i++) {
      for (size_t j = i + 1; j < v_fences.size(); j++) {
        const long long v_dist = v_fences[j] - v_fences[i];
        if (h_dist.count(v_dist)) {
          area = max(area, v_dist * v_dist);
        }
      }
    }

    if (area == 0) {
      return -1;
    } else {
      const long long mod = 1e9 + 7;
      return area % mod;
    }
  }
};
