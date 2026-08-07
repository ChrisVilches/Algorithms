#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *left, *right;
};
#endif

class Solution {
  map<int, int> levels;

  void dfs(const TreeNode* root, const int level) {
    if (root == nullptr) return;

    levels[level] = root->val;
    dfs(root->left, level + 1);
    dfs(root->right, level + 1);
  }

 public:
  vector<int> rightSideView(const TreeNode* root) {
    dfs(root, 0);

    vector<int> ans;

    for (const auto& [_, node_val] : levels) {
      ans.emplace_back(node_val);
    }

    return ans;
  }
};
