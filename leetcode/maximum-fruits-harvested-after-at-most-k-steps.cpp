#include <bits/stdc++.h>
using namespace std;

class Solution {
  int calculate(const vector<vector<int>>& fruits, const int start_pos, const int k) {
    const auto it = find_if(fruits.begin(), fruits.end(), [start_pos](const auto& el) {
      return el.front() == start_pos;
    });

    const int start_idx = distance(fruits.begin(), it);

    int i = 0;
    int left = 0, right = 0;
    int lsteps = 0, rsteps = 0;

    for (int j = start_idx - 1; j >= 0; j--) {
      const int new_lsteps = lsteps + abs(fruits[j].front() - fruits[j + 1].front());

      if (new_lsteps > k) break;

      lsteps = new_lsteps;
      i = j;
      left += fruits[j].back();
    }

    int res = left;

    for (size_t j = start_idx + 1; j < fruits.size(); j++) {
      right += fruits[j].back();
      rsteps += abs(fruits[j].front() - fruits[j - 1].front());

      while (i < start_idx && (2 * lsteps) + rsteps > k) {
        lsteps -= abs(fruits[i].front() - fruits[i + 1].front());
        left -= fruits[i].back();
        i++;
      }

      if (rsteps > k) break;

      res = max(res, left + right);
    }

    return fruits[start_idx].back() + res;
  }

 public:
  int maxTotalFruits(vector<vector<int>>& fruits, const int start_pos, const int k) {
    const bool has = any_of(fruits.begin(), fruits.end(), [start_pos](const auto& el) {
      return el.front() == start_pos;
    });

    if (!has) {
      fruits.push_back({start_pos, 0});
      sort(fruits.begin(), fruits.end());
    }

    int ans = 0;

    ans = max(ans, calculate(fruits, start_pos, k));
    reverse(fruits.begin(), fruits.end());
    ans = max(ans, calculate(fruits, start_pos, k));

    return ans;
  }
};
