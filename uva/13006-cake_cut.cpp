#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

#define MAX 200100

int N;
ld X[MAX], Y[MAX];
ld biggest_piece;
ld full_area;

ld area(int a, int b, int c){
  ld v1x = X[b] - X[a];
  ld v1y = Y[b] - Y[a];
  ld v2x = X[c] - X[a];
  ld v2y = Y[c] - Y[a];
  ld cross_k = (v1x * v2y) - (v1y * v2x);
  return abs(cross_k/2.0);
}

bool best_division(int i, int j, ld curr_area){
  ld next_area = curr_area + area(i, j, j+1);
  ld diff1 = (full_area - curr_area) - curr_area;
  ld diff2 = (full_area - next_area) - next_area;

  if(diff1 >= 0 && diff2 <= 0){
    ld bigger;
    // Must replace
    if(abs(diff1) < abs(diff2)){
      bigger = max(full_area - curr_area, curr_area);
    } else {
      bigger = max(full_area - next_area, next_area);
    }

    biggest_piece = max(biggest_piece, bigger);

    return true;
  }
  return false;
}

void solve(){
  for(int i=0; i<N; i++){
    cin >> X[i] >> Y[i];
  }

  // Make it circular (to make loop simpler)
  for(int i=0; i<N; i++){
    X[i] = X[i];
    Y[i] = Y[i];
    X[i+N] = X[i];
    Y[i+N] = Y[i];
  }

  full_area = 0;
  for(int i=1; i<N-1; i++)
    full_area += area(0, i, i+1);

  int i = 0;
  int j = 1;
  ld curr_area = 0;
  biggest_piece = 0;

  while(i<N){
    while(j < N*2 + 10){
      if(best_division(i, j, curr_area))
        break;
      curr_area += area(i, j, j+1);
      j++;
    }

    curr_area -= area(j, i, i+1);
    i++;
  }
  printf("%.0Lf %.0Lf\n", biggest_piece * 2, (full_area - biggest_piece) * 2);
}

int main(){
  while(scanf("%d", &N) == 1)
    solve();
  return 0;
}
