#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *const left, *const right;
};
#endif

class Solution {
 public:
  vector<vector<int>> closestNodes(const TreeNode* const root,
                                   const vector<int>& queries) {
    vector<int> flat;

    const function<void(const TreeNode* const)> dfs = [&](const TreeNode* const node) {
      if (node == nullptr) return;
      dfs(node->left);
      flat.emplace_back(node->val);
      dfs(node->right);
    };

    dfs(root);

    vector<vector<int>> ans(queries.size(), {-1, -1});

    vector<pair<int, int>> sorted_queries;

    for (size_t i = 0; i < queries.size(); i++) {
      sorted_queries.emplace_back(queries[i], i);
    }

    sort(sorted_queries.begin(), sorted_queries.end());

    int curr_val = -1;

    auto it = sorted_queries.begin();

    for (const int x : flat) {
      while (it != sorted_queries.end() && it->first <= x) {
        ans[it->second].front() = it->first == x ? x : curr_val;
        ans[it->second].back() = x;
        it++;
      }

      curr_val = x;
    }

    while (it != sorted_queries.end()) {
      ans[it->second].front() = flat.back();
      it++;
    }

    return ans;
  }
};
