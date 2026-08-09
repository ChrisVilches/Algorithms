#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
};

class Solution {
  bool build_path(TreeNode* node, TreeNode* target, vector<TreeNode*>& res) {
    if (node == nullptr) return false;

    if (node == target || build_path(node->left, target, res) ||
        build_path(node->right, target, res)) {
      res.emplace_back(node);
      return true;
    }

    return false;
  }

 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> path1, path2;

    build_path(root, p, path1);
    build_path(root, q, path2);

    const set<TreeNode*> path2_set{path2.begin(), path2.end()};

    for (TreeNode* n : path1) {
      if (path2_set.count(n)) return n;
    }

    assert(false);
  }
};
