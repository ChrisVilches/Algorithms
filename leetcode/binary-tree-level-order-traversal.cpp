#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  const int val;
  TreeNode *left, *right;
};

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;

    const function<void(TreeNode*, int)> dfs = [&](TreeNode* u, const int d) {
      if (u == nullptr) return;

      while (static_cast<int>(res.size()) <= d) res.emplace_back();

      res[d].emplace_back(u->val);

      dfs(u->left, d + 1);
      dfs(u->right, d + 1);
    };

    dfs(root, 0);

    return res;
  }
};
