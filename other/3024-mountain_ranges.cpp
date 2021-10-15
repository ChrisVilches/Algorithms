#include <bits/stdc++.h>

// https://www.urionlinejudge.com.br/judge/en/problems/view/3024

using namespace std;

int nums[1001];
int n, m;

int score(int starting_pos){
  int total = 1;
  for(int i=starting_pos; i<n-1; i++){
    if(nums[i+1] - nums[i] <= m){
      total++;
    } else {
      break;
    }
  }
  return total;
}

int main(){
  while(scanf("%d %d", &n, &m) == 2){
    for(int i=0; i<n; i++){
      cin >> nums[i];
    }

    int best = 0;

    for(int i=0; i<n; i++){
      best = max(best, score(i));
    }
    cout << best << endl;
  }
}
