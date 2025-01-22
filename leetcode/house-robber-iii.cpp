#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
};

class Solution {
  map<pair<TreeNode*, bool>, int> memo;

  int dp(TreeNode* root, const bool can_use) {
    if (root == nullptr) return 0;
    if (memo.count({root, can_use})) return memo[{root, can_use}];

    const int dont_use = dp(root->left, true) + dp(root->right, true);
    const int use = root->val + dp(root->left, false) + dp(root->right, false);

    int res = dont_use;

    if (can_use) {
      res = max(res, use);
    }

    return memo[{root, can_use}] = res;
  }

 public:
  int rob(TreeNode* root) { return max(dp(root, false), dp(root, true)); }
};
