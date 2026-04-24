#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  TreeNode *left, *right;
  TreeNode(const int x) : val(x), left(nullptr), right(nullptr) {}
};
#endif

class Solution {
 public:
  TreeNode* bstFromPreorder(const vector<int>& preorder) {
    size_t k = 0;

    const function<void(TreeNode* const, int, int, bool)> dfs =
        [&](TreeNode* const node, const int lo, const int hi, const bool left) {
          if (k == preorder.size() || preorder[k] < lo || hi < preorder[k]) return;

          TreeNode* const new_node = new TreeNode(preorder[k++]);

          (left ? node->left : node->right) = new_node;

          dfs(new_node, lo, new_node->val, true);
          dfs(new_node, new_node->val, hi, false);
        };

    TreeNode dummy{0};
    dfs(&dummy, INT_MIN, INT_MAX, true);

    return dummy.left;
  }
};
