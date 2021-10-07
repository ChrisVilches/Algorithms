#include <bits/stdc++.h>

using namespace std;

int nums[] = {137, 1315, 73, 136, 255, 1384, 16385};

bool is_pow2(int n){
  return !(n & (n - 1)) && n;
}

string to_str(int n){
  if(n == 1) return string("2(0)");
  int remainder = 0;
  while(!is_pow2(n)){
    n--;
    remainder++;
  }

  string ret("2");

  if(n > 2)
    ret += "(" + to_str(log2(n)) + ")";

  if(remainder > 0)
    ret += "+" + to_str(remainder);

  return ret;
}

int main(){
  for(int i=0; i<7; i++){
    cout << nums[i] << "=" << to_str(nums[i]) << endl;
  }
}
