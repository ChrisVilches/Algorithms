#include <bits/stdc++.h>

using namespace std;
double PI = 3.141592653589793238462643383279;

double D, V;

double truncated_cone_volume(double r1, double r2, double h){
  return (1/3.0) * PI * ((r1 * r1) + (r1 * r2) + (r2 * r2)) * h;
}

double cylinder_volume(double r, double h){
  return h * PI * r * r;
}

// Can also be done using math, but I prefer using binary search (it's slower though).
void solve(){
  double full_volume = cylinder_volume(D/2, D);

  double left = 0;
  double right = 1'000'000;

  while(left < right && (right - left) > 0.0000000001) {
    double d = ((right - left)/2) + left;
    double cone_height = (D - d)/2;
    if(cone_height < 0) cone_height *= -1;
    double cone_volume = truncated_cone_volume(D/2, d/2, cone_height);
    double middle_cylinder_volume = cylinder_volume(d/2, d);
    double chomped = full_volume - (cone_volume * 2) - middle_cylinder_volume;

    if(chomped < V){
      right = d;
    } else {
      left = d;
    }
  }

  printf("%0.9f\n", left);
}

int main(){
  while(scanf("%lf %lf", &D, &V)){
    if(D == 0 && V == 0) return 0;
    solve();
  }
}
