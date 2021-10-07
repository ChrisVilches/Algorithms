#include <bits/stdc++.h>

using namespace std;

int s, n;
int size[2000];
int val[2000];
int memo[2000][2000];

int knapsack(int item, int capacity){
  if(capacity <= 0) return 0;
  if(item < 0) return 0;
  if(memo[item][capacity] != -1) return memo[item][capacity];

  int without = knapsack(item-1, capacity);
  int with = capacity >= size[item] ? (val[item] + knapsack(item-1, capacity - size[item])) : 0;

  return memo[item][capacity] = max(with, without);
}

int main(){
  memset(memo, -1, sizeof memo);
  cin >> s >> n;
  for(int i=0; i<n; i++)
    cin >> size[i] >> val[i];

  cout << knapsack(n - 1, s) << endl;
}
