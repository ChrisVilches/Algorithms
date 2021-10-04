#include <bits/stdc++.h>
using namespace std;

double PI = 3.141592653589793238462643383279;
double full_weight;
double min_z = 10e9f;

struct Hole {
  double r, x, y, z;
  Hole() {
    cin >> r >> x >> y >> z;
    r /= 10e2;
    x /= 10e2;
    y /= 10e2;
    z /= 10e2;
    min_z = min(min_z, z - r); // Affect global variable.
  }
};

double cheese_block_percent_to_z(double p){
  double left = min_z;
  double right = left + 100;
  double length = right - left;
  return left + (length * p);
}

// https://en.wikipedia.org/wiki/Spherical_cap
double crown(double h, double r){
  double factor1 = (PI * h * h) / 3;
  double factor2 = (3 * r) - h;
  return factor1 * factor2;
}

double partial_volume(double z, Hole hole){
  double hole_z1 = hole.z - hole.r;
  double hole_z2 = hole.z + hole.r;
  double sphere = (4 * PI * hole.r * hole.r * hole.r)/3;

  if(z <= hole_z1) return 0;
  if(hole_z2 < z) return sphere;
  if(z < hole.z) return crown(z - hole_z1, hole.r);
    
  double cr = crown(hole_z2 - z, hole.r);
  return sphere - cr;
}

double weight(double left, double right, vector<Hole> &holes){
  double full_cheese_weight = 100 * 100 * 100;
  double right_weight = right * full_cheese_weight;
  double left_weight = left * full_cheese_weight;

  for(int i=0; i<holes.size(); i++){
    right_weight -= partial_volume(cheese_block_percent_to_z(right), holes[i]);
    left_weight -= partial_volume(cheese_block_percent_to_z(left), holes[i]);
  }
  return right_weight - left_weight;
}

double partition(double left, double right, double necessary_partitions, vector<Hole> &holes){
  double original_left = left;
  double necessary_weights = full_weight/necessary_partitions;

  while(left < right && (right - left) > 0.0000000000001){
    double mid = ((right - left)/2.0) + left;

    if(weight(original_left, mid, holes) > necessary_weights){
      right = mid;
    } else {
      left = mid;
    }
  }
  return left;
}

int main(){
  int n, s;
  double left = 0, prev_partition = 0;
  vector<double> ans;

  cin >> n >> s;
  vector<Hole> holes;
  for(int i=0; i<n; i++) holes.push_back(Hole());

  if(holes.size() == 0) min_z = 0;

  full_weight = weight(0, 1, holes);

  // A little hack so that slices are done starting from "the end of the cheese with z=0" (like the statement says).
  for(int i=0; i<holes.size(); i++){
    double z1 = min_z;
    double z2 = min_z + 100;
    double mid = z1 + ((z2 - z1)/2);

    double dist_to_mid = mid - holes[i].z - z1;
    holes[i].z = mid + dist_to_mid;
  }

  for(int i=0; i<s-1; i++){
    left = partition(left, 1, s, holes);
    ans.push_back(left - prev_partition);
    prev_partition = left;
  }

  ans.push_back(1 - prev_partition);

  for(int i=ans.size() - 1; i>=0; i--){
    printf("%0.9f\n", ans[i] * 100);
  }
}
