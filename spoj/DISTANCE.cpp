#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;

int dist(vector<int> &a, vector<int> &b){
  int total = 0;
  for(uint i=0; i<a.size(); i++){
    total += abs(a[i] - b[i]);
  }
  return total;
}

int main(){
  int n, d;
  cin >> n >> d;
  vector<vector<int>> pts;
  for(int i=0; i<n; i++){
    pts.push_back(vector<int>());
    for(int j=0; j<d; j++){
      int x;
      cin >> x;
      pts[i].push_back(x);
    }
  }

  // Filter out some points to compare.
  // Compare N (all) points with 1<<d (dimension combinations) points (avoids O(n^2) comparison).
  vector<vector<int>> pts_compare;
  int combinations = 1<<d;

  for(int c=0; c<combinations; c++){
    int max = 0;
    int idx = 0;
 
    for(int i=0; i<n; i++){
      int val=0;

      for(int j=0; j<d; j++)
        val += (c & 1<<j) ? -pts[i][j] : pts[i][j];

      if(val > max){
        max = val;
        idx = i;
      }
    }
    pts_compare.push_back(pts[idx]);
  }

  int max_dist = 0;
  for(int i=0; i<n; i++)
    for(uint j=0; j<pts_compare.size(); j++)
      max_dist = max(max_dist, dist(pts[i], pts_compare[j]));

  cout << max_dist << endl;
}
