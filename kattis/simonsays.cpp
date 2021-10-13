#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  string line;
  cin >> n;
  char skip;
  scanf("%c", &skip); 
  while(n--){
    getline(cin, line);
    if(line.rfind("Simon says ", 0) == 0){
      cout << line.substr(11, line.size()) << endl;
    }
  }
}
