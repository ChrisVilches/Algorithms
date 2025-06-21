#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : A(n + 1, 0) {}

  void update(size_t i, const int v) {
    i++;
    for (; i < A.size(); i += i & -i) A[i] += v;
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  vector<int> A;
};

class Solution {
 public:
  vector<int> resultArray(const vector<int>& nums) {
    const set<int> sorted_uniq{nums.begin(), nums.end()};
    unordered_map<int, int> idx;
    for (const int x : sorted_uniq) idx[x] = idx.size();

    array<BIT, 2> bits{BIT(idx.size()), BIT(idx.size())};
    array<vector<int>, 2> arrs;

    for (size_t i = 0; i < nums.size(); i++) {
      const int x = nums[i];

      const int n = bits[0].query(idx.size() - 1) - bits[0].query(idx[x]);
      const int m = bits[1].query(idx.size() - 1) - bits[1].query(idx[x]);

      const int j = i == 1 || n < m || (n == m && arrs[0].size() > arrs[1].size());

      bits[j].update(idx[x], 1);
      arrs[j].emplace_back(x);
    }

    arrs[0].insert(arrs[0].end(), arrs[1].begin(), arrs[1].end());
    return arrs[0];
  }
};
