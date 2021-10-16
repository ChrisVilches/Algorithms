#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> poly;

string line;

poly multiply_polynomial(poly p1, poly p2){
  poly result;
  uint degree = (p1.size() - 1) + (p2.size() - 1);
  for(uint i=0; i<=degree; i++){
    result.push_back(0);
  }

  for(uint i=0; i<p1.size(); i++){
    for(uint j=0; j<p2.size(); j++){
      ll coefficient = p1[i] * p2[j];
      ll exponent = i + j;
      result[exponent] += coefficient;
    }
  }

  return result;
}

void solve(){
  poly zeros;
  for(uint i=0; i<line.size()-1; i++){
    if(line[i] != line[i+1]){
      int citizen = 2 * (i + 1);
      zeros.push_back(citizen + 1);
    }
  }

  poly result{1};
  for(uint i=0; i<zeros.size(); i++){
    poly factor{-zeros[i], 1};
    result = multiply_polynomial(result, factor);
  }

  ll factor = 1;
  if(line[0] == 'H')
    factor = result[0] > 0 ? 1 : -1;
  else
    factor = result[0] > 0 ? -1 : 1;

  cout << result.size() - 1 << endl;

  for(int i=result.size()-1; i>=0; i--){
    cout << factor * result[i];
    if(i > 0) cout << " ";
  }
  cout << endl;
}

int main(){
  cin >> line;
  solve();
}
