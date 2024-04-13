#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class Solution {
 public:
  int find_index(const int value, const vector<int>& count) {
    if (count.size() == 1) return 0;
    int accum = 0;

    for (int i = 0; i < (int)count.size(); i++) {
      const int acc1 = accum;
      const int acc2 = accum + count[i];
      if (acc1 <= value && value < acc2) {
        return i;
      }

      accum += count[i];
    }
    assert(false);
  }

  vector<double> sampleStats(vector<int>& count) {
    ll sum = 0;
    int total_count = 0;
    ll min_val = 1e9;
    ll max_val = -1e9;
    int mode = 0;
    int mode_idx = 0;
    for (ll i = 0; i < (int)count.size(); i++) {
      sum += count[i] * i;
      total_count += count[i];
      if (count[i] != 0) {
        if (count[i] > mode) {
          mode = count[i];
          mode_idx = i;
        }
        min_val = min(min_val, i);
        max_val = max(max_val, i);
      }
    }

    double median;

    if (total_count % 2 == 0) {
      const int median1 = find_index((total_count / 2) - 1, count);
      const int median2 = find_index(total_count / 2, count);
      median = (median1 + median2) / 2.0;
    } else {
      median = find_index(total_count / 2, count);
    }

    const double mean = sum / (double)total_count;

    return vector<double>{(double)min_val, (double)max_val, (double)mean, (double)median,
                          (double)mode_idx};
  }
};
