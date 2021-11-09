#include <bits/stdc++.h>

using namespace std;

double scores[51];
int n;

double score(int except_idx){
  double accum = 0;
  int exp = 0;
  for(int i=0; i<n; i++){
    if(i == except_idx) continue;
    accum += scores[i] * pow(4/5.0, exp);
    exp++;
  }
  return accum/5;
}

int main(){
  cin >> n;
  for(int i=0; i<n; i++){
    cin >> scores[i];
  }

  printf("%f\n", score(-1));
  double sum = 0;
  for(int i=0; i<n; i++){
    sum += score(i);
  }
  printf("%f\n", sum/n);
}
