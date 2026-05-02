#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  TreeNode *left, *right;
};
#endif

class Solution {
  generator<TreeNode*> dfs(TreeNode* root) const {
    stack<TreeNode*> s;
    s.emplace(root);
    while (!s.empty()) {
      TreeNode* curr = s.top();
      s.pop();
      co_yield curr;
      if (curr != nullptr) s.emplace(curr->left);
      if (curr != nullptr) s.emplace(curr->right);
    }
  }

  vector<int> serialize(TreeNode* root) const {
    vector<int> res;

    for (TreeNode* node : dfs(root)) {
      res.emplace_back(node == nullptr ? 0 : 201 + node->val);
    }

    return res;
  }

 public:
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    vector<TreeNode*> ans;

    map<vector<int>, int> freq;

    for (TreeNode* node : dfs(root)) {
      if (node == nullptr) continue;

      const auto key = serialize(node);
      const auto it = freq.find(key);

      if (it == freq.end()) {
        freq.emplace(std::move(key), 1);
      } else if (it->second == 1) {
        ans.emplace_back(node);
        it->second = 2;
      }
    }

    return ans;
  }
};
