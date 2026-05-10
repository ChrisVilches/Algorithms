#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
};
#endif

class Solution {
 public:
  vector<int> findFrequentTreeSum(const TreeNode* const root) {
    unordered_map<int, int> freq;
    int best_freq = 0;

    const function<int(const TreeNode* const)> dfs = [&](const TreeNode* const node) {
      if (node == nullptr) return 0;

      const int sum = node->val + dfs(node->left) + dfs(node->right);
      freq[sum]++;
      best_freq = max(best_freq, freq[sum]);
      return sum;
    };

    dfs(root);

    vector<int> ans;

    for (const auto& [k, f] : freq) {
      if (f == best_freq) {
        ans.emplace_back(k);
      }
    }

    return ans;
  }
};
