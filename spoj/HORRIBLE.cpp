#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll t, n, c, p, q, v;
ll tree[1000000];
ll lazy[1000000];
void update_tree(int node, int a, int b, int i, int j, ll value) {
  
  	if(lazy[node] != 0) { // This node needs to be updated
   		tree[node] += lazy[node] * (b-a+1); // Update it

		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
    	lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}

   		lazy[node] = 0; // Reset it
  	}
  
	if(a > b || a > j || b < i) // Current segment is not within range [i, j]
		return;
    
  	if(a >= i && b <= j) { // Segment is fully within range
    		tree[node] += value * (b-a+1);

		if(a != b) { // Not leaf node
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}

    		return;
	}

	update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

	tree[node] = tree[node*2] + tree[node*2+1]; // Updating root with max value
}

/**
 * Query tree to get max element value within range [i, j]
 */
ll query_tree(int node, int a, int b, int i, int j) {
	
	if(a > b || a > j || b < i) return 0; // Out of range

	if(lazy[node] != 0) { // This node needs to be updated
		tree[node] += lazy[node] * (b-a+1); // Update it

		if(a != b) {
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}

		lazy[node] = 0; // Reset it
	}

	if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node];

	ll q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
	ll q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

	ll res = q1 + q2; // Return final result
	
	return res;
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
