#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll t, n, c, p, q, v;
ll tree[1000000];
ll lazy[1000000];

void propagate_one_level(int node, int a, int b){
  if(lazy[node] == 0) return;
  tree[node] += lazy[node] * (b - a + 1);

  if(a != b) {
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node];
  }

  lazy[node] = 0;
}

// Update [i, j]
void update_tree(int node, int a, int b, int i, int j, ll value) {
  propagate_one_level(node, a, b);

  if(a > b || a > j || b < i)
    return;

  if(a >= i && b <= j) {
    tree[node] += value * (b - a + 1);
    if(a != b) {
      lazy[node * 2] += value;
      lazy[node * 2 + 1] += value;
    }
    return;
  }

  update_tree(node * 2, a, (a + b)/2, i, j, value);
  update_tree(1 + node * 2, 1 + (a + b)/2, b, i, j, value);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// Query [i, j]
ll query_tree(int node, int a, int b, int i, int j) {
  if(a > b || a > j || b < i) return 0;

  propagate_one_level(node, a, b);

  if(a >= i && b <= j)
    return tree[node];

  ll q1 = query_tree(node * 2, a, (a + b)/2, i, j);
  ll q2 = query_tree(1 + node * 2, 1 + (a + b)/2, b, i, j);

  return q1 + q2;
}

void solve(){
  int type;
  cin >> n >> c;
  memset(tree, 0, sizeof tree);
  memset(lazy, 0, sizeof lazy);

  while (c--){
    cin >> type >> p >> q;
    p--;
    q--;
    if (type) {
      cout << query_tree(1, 0, n - 1, p, q) << endl;
    } else {
      cin >> v;
      update_tree(1, 0, n - 1, p, q, v);
    }
  }
}

int main(){
  cin >> t;
  while (t--)
    solve();
}
