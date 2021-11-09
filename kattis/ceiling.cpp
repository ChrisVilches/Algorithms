#include <bits/stdc++.h>

using namespace std;

int n, k;

// no destructor
struct Tree {
  int value = -1;
  Tree* left = nullptr;
  Tree* right = nullptr;
};

void insert(Tree* t, int node){
  if(t->value <= node){
    if(t->right){
      insert(t->right, node);
    } else {
      t->right = new Tree();
      t->right->value = node;
    }
  } else {
    if(t->left){
      insert(t->left, node);
    } else {
      t->left = new Tree();
      t->left->value = node;
    }
  }
}

long long hash_tree(Tree* t, int factor){
  long long total = 0;

  if(t->left)
    total += 0x7c2123c * hash_tree(t->left, factor + 1) * factor;
  else
    total += 0xc343455 * factor;

  if(t->right)
    total += 0x919113 * hash_tree(t->right, factor + 2) * factor;
  else
    total += 0x2af4343 * factor;

  return total;
}

void solve(){
  int node;
  unordered_map<long long, int> counts;
  for(int i=0; i<n; i++){
    Tree t;
    cin >> t.value;
    for(int j=1; j<k; j++){
      cin >> node;
      insert(&t, node);
    }

    long long h = hash_tree(&t, 1);

    if(counts.find(h) != counts.end())
      counts[h]++;
    else
      counts[h] = 1;
  }

  cout << counts.size() << endl;
}

int main(){
  while(scanf("%d %d", &n, &k) == 2) solve();
  return 0;
}
