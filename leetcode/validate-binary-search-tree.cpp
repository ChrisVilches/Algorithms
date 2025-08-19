#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
};

class Solution {
  bool is_valid(TreeNode* root, const long long lo, const long long hi) const {
    if (root == nullptr) return true;
    if (root->val <= lo || root->val >= hi) return false;

    const int val = root->val;

    if (root->left && val <= root->left->val) return false;
    if (root->right && val >= root->right->val) return false;

    return is_valid(root->left, lo, val) && is_valid(root->right, val, hi);
  }

 public:
  bool isValidBST(TreeNode* root) { return is_valid(root, LONG_LONG_MIN, LONG_LONG_MAX); }
};
