#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : A(n + 1, 0) {}

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void set_one(const int i, const int val) {
    clear_one(i);
    update(i, val);
  }

 private:
  void update(size_t i, const int v) {
    i++;
    for (; i < A.size(); i += i & -i) A[i] += v;
  }
  int query_one(const int i) { return query(i) - query(i - 1); }
  void clear_one(const int i) { update(i, -query_one(i)); }
  vector<int> A;
};

class Solution {
  int n;
  vector<int> nums;
  BIT bit{0};

  void set_peak(const int idx) {
    if (idx <= 0 || idx >= n - 1) return;

    bit.set_one(idx, nums[idx - 1] < nums[idx] && nums[idx] > nums[idx + 1]);
  }

 public:
  vector<int> countOfPeaks(const vector<int>& input, const vector<vector<int>>& queries) {
    this->nums = input;
    this->n = input.size();
    bit = BIT(n);

    for (int i = 0; i < n; i++) {
      set_peak(i);
    }

    vector<int> ans;

    for (const vector<int>& q : queries) {
      if (q.front() == 1) {
        const int l = q[1] + 1;
        const int r = q[2] - 1;
        const int count = bit.query(r) - bit.query(l - 1);
        ans.emplace_back(max(count, 0));
      } else {
        const int idx = q[1];
        const int val = q[2];

        this->nums[idx] = val;

        set_peak(idx - 1);
        set_peak(idx);
        set_peak(idx + 1);
      }
    }

    return ans;
  }
};
