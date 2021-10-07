#include <bits/stdc++.h>

using namespace std;

int b, s, niceness[100000];

void solve(int r){
  for(int i=0; i<s - 1; i++)
    cin >> niceness[i];

  int result_i, result_j;

  int i=0;
  int sum = 0;
  int max_sum = INT_MIN;

  for(int j=0; j < s - 1; j++){
    sum += niceness[j];
    if(sum < 0){
      i = j + 1;
      sum = 0;
    }

    // Replace values
    bool same_sum_but_longer = sum == max_sum && (result_j - result_i < j - i);

    if(sum > max_sum || same_sum_but_longer){
      max_sum = sum;
      result_i = i;
      result_j = j;
    }
  }

  if(max_sum > 0) {
    printf("The nicest part of route %d is between stops %d and %d\n", r, result_i + 1, result_j + 2);
  } else {
    printf("Route %d has no nice parts\n", r);
  }
}

int main(){
  cin >> b;
  for(int i=0; i<b; i++){
    cin >> s;
    solve(i + 1);
  }
}
