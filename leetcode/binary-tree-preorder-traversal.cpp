#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
  vector<int> res;

  void dfs(TreeNode* node) {
    if (node == nullptr) return;
    res.emplace_back(node->val);
    dfs(node->left);
    dfs(node->right);
  }

 public:
  vector<int> preorderTraversal(TreeNode* root) {
    dfs(root);
    return res;
  }
};
