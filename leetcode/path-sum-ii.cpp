#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
};

class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, const int target) {
    vector<vector<int>> ans;
    vector<int> curr_path;
    int curr_sum = 0;

    const function<void(TreeNode*)> dfs = [&](TreeNode* node) {
      if (node == nullptr) return;

      curr_sum += node->val;
      curr_path.emplace_back(node->val);

      const bool is_leaf = node->left == nullptr && node->right == nullptr;

      if (is_leaf && curr_sum == target) {
        ans.emplace_back(curr_path);
      }

      dfs(node->left);
      dfs(node->right);

      curr_path.pop_back();
      curr_sum -= node->val;
    };

    dfs(root);

    return ans;
  }
};
