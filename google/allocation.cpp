#include <bits/stdc++.h>

using namespace std;

void solve(){
  vector<int> nums;
  int n;
  int b;
  cin >> n >> b;
  for(int i=0; i<n; i++){
    int x;
    cin >> x;
    nums.push_back(x);
  }

  sort(nums.begin(), nums.end());

  int total = 0;
  for(int i=0; i<n; i++){
    if(nums[i] <= b){
      b -= nums[i];
      total++;
    }
  }
  cout << total << endl;
}

int main(){
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    printf("Case #%d: ", i+1);
    solve();
  }

  return 0;
}
