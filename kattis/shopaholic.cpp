#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll nums[200001];

int main(){
  int n;
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> nums[i];

  sort(nums, nums + n);
  int count = 1;
  ll discount = 0;
  for(int i=n-1; i>=0; i--){
    if(count == 3){
      count = 1;
      discount += nums[i];
    } else {
      count++;
    }
  }
  cout << discount << endl;
}
