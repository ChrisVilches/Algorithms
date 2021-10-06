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

vector<Node> tree;

int query(Node &subtree, int i, int j, int orig_i, int orig_j){
  if(i > j){
    return INT_MIN;
  }
  if(subtree.j < orig_i) return INT_MIN;
  if(orig_j < subtree.i) return INT_MIN;

  //printf("subtree (%d %d) query (%d %d) orig query (%d %d)\n", subtree.i, subtree.j, i, j, orig_i, orig_j);

  // Node has exact query.
  if(subtree.i == i && subtree.j == j)
    return subtree.freq;
  if(subtree.i == orig_i && subtree.j == orig_j)
    return subtree.freq;

  // Is leaf.
  if(!subtree.left && !subtree.right){
    int total = subtree.freq - abs(i - subtree.i) - abs(j - subtree.j);
    return total;
  }
  //cout << "branch query" << endl;

  int a = query(*subtree.left, max(subtree.left->i, orig_i), min(orig_j, subtree.left->j), orig_i, orig_j);
  int b = query(*subtree.right, max(subtree.right->i, orig_i), min(orig_j, subtree.right->j), orig_i, orig_j);

  return max(a, b);
}

void solve(){
  tree.clear();
  for(int i=0; i<n; i++)
    scanf("%d", &nums[i]);

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

  // Make it even by pushing the last node again.
  if(tree.size() % 2 != 0){
    tree.push_back(last_node);
  }

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
    // Make it even by pushing the last node again.
    if(tree.size() % 2 != 0){
      //tree.push_back(tree[tree.size() - 1]);
    }
  }

  Node* root = &tree[tree.size() - 1];


 // cout << "tree has " << tree.size() << " nodes" << endl;

  while(q--){
    int i, j;
    scanf("%d %d", &i, &j);
    printf("%d\n", query(*root, i - 1, j - 1, i - 1, j - 1));
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
