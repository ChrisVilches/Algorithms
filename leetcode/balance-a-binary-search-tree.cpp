#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *left, *right;
  TreeNode(const int x, const TreeNode* left, const TreeNode* right)
      : val(x), left(left), right(right) {}
};
#endif

class Solution {
  vector<int> flat;

  void dfs(const TreeNode* node) {
    if (node == nullptr) return;
    dfs(node->left);
    flat.emplace_back(node->val);
    dfs(node->right);
  }

  TreeNode* recur(const int l, const int r) const {
    if (l > r) return nullptr;

    const int m = (l + r) / 2;
    return new TreeNode(flat[m], recur(l, m - 1), recur(m + 1, r));
  }

 public:
  TreeNode* balanceBST(const TreeNode* root) {
    dfs(root);
    return recur(0, flat.size() - 1);
  }
};
