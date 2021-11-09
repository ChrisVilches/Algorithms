#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
enum {
  P = 'P',
  E = 'E'
};

string cake;
int N, B;

char fruit_at(int i){
  return cake[i % N];
}

void solve(){
  N = cake.size();
  cin >> B;
  ull total = 0;
  int last_e_pos = -1;

  for(int i=B-1; i>=0; i--){
    if(cake[i] == E){
      last_e_pos = i;
      break;
    }
  }

  for(int i=0; i<N; i++){
    int range_end_pos = i+B-1;
    if(fruit_at(range_end_pos) == E)
      last_e_pos = range_end_pos;

    bool contains_e = i <= last_e_pos && last_e_pos <= range_end_pos;

    if(contains_e){
      ull add = B;

      if(fruit_at(range_end_pos) == P)
        add -= range_end_pos - last_e_pos;

      total += add;
    }
  }

  cout << total << endl;
}

int main(){
  while(getline(cin, cake)){
    if(cake[0] != P && cake[0] != E) continue;
    solve();
  }
}
