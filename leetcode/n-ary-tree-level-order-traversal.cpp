#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
class Node {
 public:
  const int val;
  const vector<const Node*> children;
};
#endif

class Solution {
  vector<vector<int>> levels;

  void dfs(const Node* const node, const size_t level) {
    if (node == nullptr) return;

    if (levels.size() < level + 1) {
      levels.emplace_back();
    }

    levels[level].emplace_back(node->val);

    for (const Node* const child : node->children) {
      dfs(child, level + 1);
    }
  }

 public:
  vector<vector<int>> levelOrder(const Node* const root) {
    dfs(root, 0);
    return levels;
  }
};
