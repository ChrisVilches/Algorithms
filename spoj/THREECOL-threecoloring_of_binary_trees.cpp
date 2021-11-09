#include <bits/stdc++.h>

using namespace std;

#define N 10030

enum { R = 0, G = 1, B = 2 };
enum { MIN = 0, MAX = 1 };

string line;

int memo[N][3][2], pos, node_idx;

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int idx;
  Node(int idx) : idx(idx) {}
  ~Node() {
    if (left) delete left;
    if (right) delete right;
  }
};

int dp(Node* node, int color, int fn) {
  if (node == nullptr) return 0;
  int idx = node->idx;

  if (memo[idx][color][fn] != -1) return memo[idx][color][fn];

  vector<int> colors{R, G, B};
  colors.erase(find(colors.begin(), colors.end(), color));

  int val1 = dp(node->left, colors[0], fn) + dp(node->right, colors[1], fn);
  int val2 = dp(node->left, colors[1], fn) + dp(node->right, colors[0], fn);
  int ret = (color == G) + (fn ? max(val1, val2) : min(val1, val2));

  return (memo[idx][color][fn] = ret);
}

void insert(Node* subtree) {
  char c = line.at(pos);
  if (c == '0') return;
  subtree->left = new Node(node_idx++);
  pos++;
  insert(subtree->left);

  if (c != '2') return;
  subtree->right = new Node(node_idx++);
  pos++;
  insert(subtree->right);
}

void solve() {
  memset(memo, -1, sizeof memo);
  node_idx = 0;
  pos = 0;
  cin >> line;

  Node tree(node_idx++);
  insert(&tree);
  int maximal = max({dp(&tree, R, MAX), dp(&tree, G, MAX), dp(&tree, B, MAX)});
  int minimal = min({dp(&tree, R, MIN), dp(&tree, G, MIN), dp(&tree, B, MIN)});

  printf("%d %d\n", maximal, minimal);
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}
