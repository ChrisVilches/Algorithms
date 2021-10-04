#include <bits/stdc++.h>

using namespace std;

double PI = 3.141592653589793238462643383279;
double full_weight;
double min_z;

struct Hole {
  double r, x, y, z;
  Hole(double r, double x, double y, double z){
    this->r = r;
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Hole() {
    cin >> r >> x >> y >> z;
    r /= 10e2;
    x /= 10e2;
    y /= 10e2;
    z /= 10e2;

    //fprintf(stderr, "Hole: %f %f %f %f\n", r, x, y, z);
  }
};

double cheese_block_percent_to_z(double p){
  if(p > 1) throw invalid_argument("cheese_block_percent_to_z Only allows numbers from 0 to 1");
  double left = min_z;
  double right = left + 100;
  double length = right - left;
  return left + (length * p);
}

// https://en.wikipedia.org/wiki/Spherical_cap
double partial_volume(double z, Hole hole){
  double hole_z1 = hole.z - hole.r;
  double hole_z2 = hole.z + hole.r;
  double sphere = (4 * PI * hole.r * hole.r * hole.r)/3;

  if(z <= hole_z1){
     return 0;
  } else if(hole_z2 < z) {
    return sphere;
  }
  else if(z < hole.z) {
    double h = z - hole_z1;
    double factor1 = (PI * h * h) / 3;
    double factor2 = (3 * hole.r) - h;
    return factor1 * factor2;
  } else {
    double h = hole_z2 - z;
    double factor1 = (PI * h * h) / 3;
    if(h > hole.r){
      throw invalid_argument("wat");
    }
    double factor2 = (3 * hole.r) - h;
    double crown = factor1 * factor2;
    return sphere - crown;
  }
}

double weight(double left, double right, vector<Hole> &holes){
  if(right > 1) throw invalid_argument("(right) Only allows numbers from 0 to 1");
  if(left > 1) throw invalid_argument("(left) Only allows numbers from 0 to 1");
  // TODO: Must sort holes by Z axis I think... (so I can use binary search to know which holes are inside the partition)
  //       This sorting should be done before the call to this function though.

  if(left > right){
    throw invalid_argument("left > right");
  }

  double full_cheese_weight = 100 * 100 * 100;
  double right_weight = right * full_cheese_weight;
  double left_weight = left * full_cheese_weight;

  for(int i=0; i<holes.size(); i++){
    //fprintf(stderr, "vol sphere: %f\n", partial_volume(cheese_block_percent_to_z(right), holes[i]));
    right_weight -= partial_volume(cheese_block_percent_to_z(right), holes[i]);
    left_weight -= partial_volume(cheese_block_percent_to_z(left), holes[i]);

  }
  //printf("left and right weights %f - %f\n", left_weight, right_weight);
  return right_weight - left_weight;
}

double partition(double left, double right, double necessary_partitions, vector<Hole> &holes){
  if(right > 1) throw invalid_argument("partition (right) Only allows numbers from 0 to 1");
  if(left > 1) throw invalid_argument("partition (left) Only allows numbers from 0 to 1");
  double original_left = left;

  double iter = 10e9;
  while(left < right && (right - left) > 0.0000000000001){
    double mid = ((right - left)/2.0) + left;

    double necessary_weights = full_weight/necessary_partitions;

    double w = weight(original_left, mid, holes);
    //printf("[%0.4f, (%0.4f), %0.4f] ---- Needs %f and got %f\n", left, mid, right, necessary_weights, w);

    if(w > necessary_weights){
      right = mid;
    } else {
      left = mid;
    }
  }
  return left;
}

int main(){
  int n, s;
  cin >> n >> s;

  vector<Hole> holes;

  for(int i=0; i<n; i++){
    holes.push_back(Hole());
  }

  min_z = 10e9f;

  for(int i=0; i<holes.size(); i++){
    Hole h = holes[i];
    min_z = min(min_z, h.z - h.r);
  }

  if(holes.size() == 0){
    min_z = 0;
  }

  //cerr << "MIN Z: " << min_z << endl;

  double left = 0;
  double right = 1;

  full_weight = weight(0, 1, holes);

  double prev_partition = 0;
  double sum = 0.0;
  double sum_weights = 0.0;

  for(int i=0; i<holes.size(); i++){
    double z1 = min_z;
    double z2 = min_z + 100;
    double mid = z1 + ((z2 - z1)/2);

    double dist_to_mid = mid - holes[i].z - z1;
    holes[i].z = mid + dist_to_mid;
  }

  sort(holes.begin(), holes.end(), [](auto a, auto b) -> bool
  { 
      return a.z > b.z; 
  });

  vector<double> ans;

  for(int i=0; i<s-1; i++){
    left = partition(left, right, s, holes);

    sum += 100 * (left - prev_partition);
    sum_weights += weight(prev_partition, left, holes);
    
    //printf("%0.9f (weight: %f)\n", 100 * (left - prev_partition), weight(prev_partition, left, holes));
    //printf("%0.9f\n", 100 * (left - prev_partition));
    ans.push_back(100 * (left - prev_partition));
    //cout << "------------- partition end --------------- " << endl << endl;
    prev_partition = left;
    //break;
  }

  double last = 1 - prev_partition;
  sum += 100 * last;
  double last_weight = weight(prev_partition, 1, holes);
  sum_weights += last_weight;

  //printf("%0.9f (weight: %f)\n", 100 * last, last_weight);
  ans.push_back(100 * last);
  //printf("%0.9f\n", 100 * last);
  //fprintf(stderr, "Full weight: %f\n", full_weight);
  //fprintf(stderr, "Sum weights: %f\n", sum_weights);
  //cerr << "SUM: " << sum << endl;

  for(int i=ans.size() - 1; i>=0; i--){
    printf("%0.9f\n", ans[i]);
  }
}
