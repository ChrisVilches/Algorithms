#include <bits/stdc++.h>

using namespace std;

bool eye(char c){
  return c == ':' || c == ';';
}

int main(){
  string str;
  cin >> str;

  for(int i=1; i<str.size(); i++){
    if(str[i] != ')') continue;

    if(eye(str[i-1])){
      cout << i-1 << endl;
    }

    if(i < 2) continue;

    if(str[i-1] != '-') continue;

    if(eye(str[i-2])){
      cout << i-2 << endl;
    }
  }
}
