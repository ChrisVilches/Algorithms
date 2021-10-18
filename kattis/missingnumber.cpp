#include <bits/stdc++.h>

using namespace std;

vector<string> build_correct_digits(){
  vector<string> result;
  for(int i=1; i<=100; i++){
    stringstream s;
    if(i < 10){
      s << i;
      result.push_back(s.str());
    } else {
      int ten = (i/10);
      int unit = (i%10);
      s << ten << unit;
      result.push_back(s.str());
    }
  }
  return result;
}

int main(){
  int n;
  cin >> n;
  vector<string> correct_digits = build_correct_digits();
  string input_digits;
  cin >> input_digits;

  int pos = 0;
  for(string digits : correct_digits){
    if(input_digits.compare(pos, digits.size(), digits, 0, digits.size()) != 0){
      cout << digits << endl;
      break;
    }
    pos += digits.size();
  }
}
