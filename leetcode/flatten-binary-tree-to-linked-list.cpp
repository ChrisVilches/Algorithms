#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  void flatten(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    vector<int> nums;

    const function<void(TreeNode *)> dfs = [&](const TreeNode *node) {
      if (node == nullptr) {
        return;
      }

      nums.emplace_back(node->val);
      dfs(node->left);
      dfs(node->right);
    };

    dfs(root);

    root->left = nullptr;

    TreeNode *curr = root;

    for (int i = 1; i < (int)nums.size(); i++) {
      curr->right = new TreeNode;
      curr = curr->right;
      curr->val = nums[i];
    }
  }
};
