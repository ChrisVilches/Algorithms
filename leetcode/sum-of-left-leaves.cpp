#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *left, *right;
};
#endif

class Solution {
  bool is_leaf(const TreeNode* node) const {
    return node->left == nullptr && node->right == nullptr;
  }

  int dfs(const TreeNode* root, const bool is_left) const {
    if (root == nullptr) return 0;

    int res = 0;

    if (is_leaf(root) && is_left) {
      res += root->val;
    }

    res += dfs(root->left, true);
    res += dfs(root->right, false);

    return res;
  }

 public:
  int sumOfLeftLeaves(const TreeNode* root) { return dfs(root, false); }
};
