#include <bits/stdc++.h>
using namespace std;

#ifdef DEV
struct TreeNode {
  const int val;
  const TreeNode *left, *right;
};
#endif

class Solution {
  using ll = long long;
  const ll mod = 1e9 + 7;
  unordered_map<const TreeNode*, ll> sums;

  void post_order_dfs(const TreeNode* root, const function<void(const TreeNode*)>& fn) {
    if (root == nullptr) return;

    post_order_dfs(root->left, fn);
    post_order_dfs(root->right, fn);

    fn(root);
  }

 public:
  int maxProduct(const TreeNode* root) {
    post_order_dfs(root, [&](const TreeNode* root) {
      sums[root] = root->val + sums[root->left] + sums[root->right];
    });

    const ll total = sums[root];
    ll ans = 1;

    post_order_dfs(root, [&](const TreeNode* root) {
      const ll prod1 = (total - sums[root->left]) * sums[root->left];
      const ll prod2 = (total - sums[root->right]) * sums[root->right];

      ans = max({ans, prod1, prod2});
    });

    return ans % mod;
  }
};
