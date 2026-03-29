#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  const int val;
  const TreeNode *left, *right;
};

class Solution {
  map<int, int> sums;

  void dfs(const TreeNode* root, const int level) {
    if (root == nullptr) return;

    sums[level] += root->val;
    dfs(root->left, level + 1);
    dfs(root->right, level + 1);
  }

 public:
  int maxLevelSum(const TreeNode* root) {
    dfs(root, 1);

    int max_val = INT_MIN;
    int ans = 0;

    for (const auto& [level, sum] : sums) {
      if (max_val < sum) {
        max_val = sum;
        ans = level;
      }
    }

    return ans;
  }
};
