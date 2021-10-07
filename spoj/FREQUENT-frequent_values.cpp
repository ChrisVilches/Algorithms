#include <bits/stdc++.h>

using namespace std;

int n, q, nums[100000];

struct Node {
  int i, j, freq;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(int _i, int _j, int _freq) : i(_i), j(_j), freq(_freq) {}
  Node(Node *l, Node *r) : left(l), right(r) {
    i = min(l->i, r->i);
    j = max(l->j, r->j);
    freq = max(l->freq, r->freq);
  }
};

vector<Node> tree;

int query(Node &subtree, int i, int j, int orig_i, int orig_j){
  if(subtree.j < orig_i || orig_j < subtree.i) return INT_MIN;

  if(subtree.i == i && subtree.j == j) return subtree.freq;

  if(!subtree.left && !subtree.right)
    return subtree.freq - abs(i - subtree.i) - abs(j - subtree.j);

  return max(
    query(*subtree.left, max(subtree.left->i, i), min(j, subtree.left->j), orig_i, orig_j),
    query(*subtree.right, max(subtree.right->i, i), min(j, subtree.right->j), orig_i, orig_j)
  );
}

void create_leafs(){
  int prev = nums[0];
  int from = 0;
  for(int i=1; i<n; i++){
    if(nums[i] == prev) continue;
    prev = nums[i];
    tree.push_back(Node(from, i - 1, i - from));
    from = i;
  }

  // Close last set (edge case).
  tree.push_back(Node(from, n - 1, n - from));
}

void create_parent_nodes(){
  int n_idx = 0;
  while(tree.size() - n_idx > 1){
    int size = tree.size();
    for(; n_idx<size; n_idx+=2)
      tree.push_back(Node(&tree[n_idx], &tree[n_idx + 1]));
  }
}

void solve(){
  tree.clear();
  for(int i=0; i<n; i++) scanf("%d", &nums[i]);
  create_leafs();
  create_parent_nodes();

  while(q--){
    int i, j;
    scanf("%d %d", &i, &j);
    printf("%d\n", query(tree[tree.size() - 1], i - 1, j - 1, i - 1, j - 1));
  }
}

int main(){
  tree.reserve(100000 * 40); // avoid realloc
  while(scanf("%d", &n) == 1){
    if(n == 0) break;
    scanf("%d", &q);
    solve();
  }
}
