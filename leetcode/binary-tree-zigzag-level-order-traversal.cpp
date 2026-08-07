#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
};

class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    map<int, vector<int>> levels;

    const function<void(TreeNode*, int)> dfs = [&](TreeNode* node, const int level) {
      if (node == nullptr) return;

      levels[level].emplace_back(node->val);
      dfs(node->left, level + 1);
      dfs(node->right, level + 1);
    };

    dfs(root, 0);

    vector<vector<int>> ans;

    for (auto& [level, nodes] : levels) {
      if (level % 2 == 1) {
        reverse(nodes.begin(), nodes.end());
      }

      ans.emplace_back(nodes);
    }

    return ans;
  }
};
