#include <bits/stdc++.h>

using namespace std;

char text[50][50];

int main(){
  int r, c, zr, zc;
  cin >> r >> c >> zr >> zc;

  for(int i=0; i<r; i++){
    scanf("%s", &text[i]);
  }

  for(int i=0; i<r; i++){
    for(int i2=0; i2<zr; i2++){
      for(int j=0; j<c; j++)
        for(int j2=0; j2<zc; j2++)
          cout << text[i][j];
      cout << endl;
    }
  }
}
