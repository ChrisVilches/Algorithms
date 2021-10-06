#include <bits/stdc++.h>

using namespace std;

int n, q;
int nums[100000];

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

// TODO: Use normal stacked array
vector<Node> tree;

int query(Node &subtree, int i, int j, int orig_i, int orig_j){
  if(subtree.j < orig_i || orig_j < subtree.i) return INT_MIN;

  if(subtree.i == i && subtree.j == j)
    return subtree.freq;

  if(!subtree.left && !subtree.right)
    return subtree.freq - abs(i - subtree.i) - abs(j - subtree.j);

  // TODO: Can this be simplified (i.e. max & min)? it's hecka hard to read.
  return max(
    query(*subtree.left, max(subtree.left->i, i), min(j, subtree.left->j), orig_i, orig_j),
    query(*subtree.right, max(subtree.right->i, i), min(j, subtree.right->j), orig_i, orig_j)
  );
}

void solve(){
  tree.clear();
  for(int i=0; i<n; i++)
    scanf("%d", &nums[i]);

  // TODO: Tree creation is kinda backwards. Can I fix this to make it more intuitive?

  int prev = nums[0];
  int from = 0;
  for(int i=1; i<n; i++){
    if(nums[i] == prev) continue;
    Node n(from, i - 1, i - from);
    prev = nums[i];
    tree.push_back(n);
    from = i;
  }

  // Add last one (edge case).
  Node last_node = Node(from, n - 1, n - from);
  tree.push_back(last_node);

  int n_idx = 0;

  while(tree.size() - n_idx){
    int tree_size = tree.size();
    if(tree_size - 1 - n_idx == 1){
      tree.push_back(Node(&tree[tree_size - 2], &tree[tree_size - 1]));
      break;
    }
    for(; n_idx<tree_size-1; n_idx+=2){
      tree.push_back(Node(&tree[n_idx], &tree[n_idx + 1]));
    }
  }

  while(q--){
    int i, j;
    scanf("%d %d", &i, &j);
    printf("%d\n", query(tree[tree.size() - 1], i - 1, j - 1, i - 1, j - 1));
  }
}

int main(){
  tree.reserve(100000 * 40); // Avoid dangling pointers.
  while(scanf("%d", &n) == 1){
    if(n == 0) break;
    scanf("%d", &q);
    solve();
  }
}
