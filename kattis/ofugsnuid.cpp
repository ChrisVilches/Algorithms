#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  vector<int> nums;
  cin >> n;
  while(n--){
    int num;
    cin >> num;
    nums.push_back(num);
  }

  for(int i=nums.size()-1; i>=0; i--){
    cout << nums[i] << endl;
  }
}
