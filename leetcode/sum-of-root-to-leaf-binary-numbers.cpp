#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
};
#endif

class Solution {
  int dfs(const TreeNode* const node, const int val) {
    if (node == nullptr) return 0;
    const int next_val = (val * 2) | node->val;

    if (node->left == nullptr && node->right == nullptr) {
      return next_val;
    }

    return dfs(node->left, next_val) + dfs(node->right, next_val);
  }

 public:
  int sumRootToLeaf(const TreeNode* const root) { return dfs(root, 0); }
};
