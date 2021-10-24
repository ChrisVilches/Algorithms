#include <bits/stdc++.h>

using namespace std;

enum { R = 0, G = 1, B = 2 };

#define N 10030

string line;

int memo[N][3][2];
int pos, node_idx;

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

int dp(Node* node, int color, int maximal) {
  if (node == nullptr) return 0;
  int idx = node->idx;

  if (memo[idx][color][maximal] != -1) return memo[idx][color][maximal];

  if (!node->left && !node->right) return color == G;

  int ret = color == G;
  int val1, val2;

  vector<int> available_colors{R, G, B};
  available_colors.erase(
      find(available_colors.begin(), available_colors.end(), color));

  val1 = dp(node->left, available_colors[0], maximal) +
         dp(node->right, available_colors[1], maximal);
  val2 = dp(node->left, available_colors[1], maximal) +
         dp(node->right, available_colors[0], maximal);
  ret += maximal ? max(val1, val2) : min(val1, val2);

  return (memo[idx][color][maximal] = ret);
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
  int maximal = max({dp(&tree, R, 1), dp(&tree, G, 1), dp(&tree, B, 1)});
  int minimal = min({dp(&tree, R, 0), dp(&tree, G, 0), dp(&tree, B, 0)});

  printf("%d %d\n", maximal, minimal);
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}
