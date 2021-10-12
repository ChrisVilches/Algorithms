#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> p;
double R = 100;
double PI = 3.141592653589793238462643383279;
p goal;
int N;
bool bools[2] = {false, true};
p poles[8];

double sq(double x) {
    return x * x;
}

void validate_point_belongs_to_circle(p point_in_circle, p circle_center, string msg);
void validate_point_belongs_to_circle(p point_in_circle, p circle_center);
pair<pair<p,p>,bool> valid_line_from_point_to_circle_border(p p1, p circle_center, bool which, int excepting);
constexpr auto eps = 1e-14;



double dist(p p1, p p2){
  double a = p1.first - p2.first;
  double b = p1.second - p2.second;
  return sqrt((a*a) + (b*b));
}

void expect(bool assertion, int id){
  if(!assertion){
    string msg;
    msg = "Failed: " + to_string(id);
    cout << msg << endl;
    //throw runtime_error(msg);
  }
}
bool err_eq(double a, double b){
  return abs(a - b) < 0.000000001;
}

double tang2_length(double circle_dist){
  double half_dist = (circle_dist/2);
  return 2 * sqrt((half_dist * half_dist) - (R * R));
}
bool line_eq(pair<p, p> line1, pair<p, p> line2){
  bool a = err_eq(line1.first.first , line2.first.first);
  bool b = err_eq(line1.first.second , line2.first.second);
  bool c = err_eq(line1.second.first , line2.second.first);
  bool d = err_eq(line1.second.second , line2.second.second);
  return a && b && c && d;
}

double dist(double px, double py, double x1, double y1){
  return dist(make_pair(px, py), make_pair(x1, y1));
}

double dist(p p1){
  return dist(make_pair(0, 0), p1);
}

double dist(pair<p,p> line){
  return dist(line.first, line.second);
}

bool pointCircle(double px, double py, double cx, double cy, double r) {

  // get distance between the point and circle's center
  // using the Pythagorean Theorem
  double distX = px - cx;
  double distY = py - cy;
  double distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the circle's
  // radius the point is inside!
  if (distance <= r) {
    return true;
  }
  return false;
}

// LINE/POINT
bool linePoint(double x1, double y1, double x2, double y2, double px, double py) {

  // get distance from the point to the two ends of the line
  double d1 = dist(px,py, x1,y1);
  double d2 = dist(px,py, x2,y2);

  // get the length of the line
  double lineLen = dist(x1,y1, x2,y2);

  // since doubles are so minutely accurate, add
  // a little buffer zone that will give collision
  double buffer = 0.1;    // higher # = less accurate

  // if the two distances are equal to the line's
  // length, the point is on the line!
  // note we use the buffer here to give a range,
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return true;
  }
  return false;
}

bool intersects(double x1, double y1, double x2, double y2, double cx, double cy) {
  double radius = R - 0.00000001;

  // is either end INSIDE the circle?
  // if so, return true immediately
  bool inside1 = pointCircle(x1,y1, cx,cy, radius);
  bool inside2 = pointCircle(x2,y2, cx,cy, radius);
  if (inside1 || inside2) return true;

  // get length of the line
  double distX = x1 - x2;
  double distY = y1 - y2;
  double len = sqrt( (distX*distX) + (distY*distY) );

  // get dot product of the line and circle
  double dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

  // find the closest point on the line
  double closestX = x1 + (dot * (x2-x1));
  double closestY = y1 + (dot * (y2-y1));

  // is this point actually on the line segment?
  // if so keep going, but if not, return false
  bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
  if (!onSegment) return false;

  // get distance to closest point
  distX = closestX - cx;
  distY = closestY - cy;
  double distance = sqrt( (distX*distX) + (distY*distY) );

  if (distance < radius) {
    return true;
  }
  return false;
}

bool intersects(p p1, p p2, p cp){
  return intersects(p1.first, p1.second, p2.first, p2.second, cp.first, cp.second);
}

void print_line(pair<p, p> line){
  fprintf(stderr, "Line: %f, %f --> %f, %f\n", line.first.first, line.first.second, line.second.first, line.second.second);
}

p vector_diff(p v1, p v2){
  return make_pair(v1.first - v2.first, v1.second - v2.second);
}

bool line_intersects_any(p p1, p p2, int excepting){
  for(int i=0; i<N; i++){
    if((excepting & (1<<i)) > 0) continue;
    if(intersects(p1, p2, poles[i])){
      return true;
    }
  }
  return false;
}

bool line_intersects_any(p p1, p p2){
  return line_intersects_any(p1, p2, 0);
}
void validate_point_belongs_to_circle(p point_in_circle, p circle_center, string msg){ // R always the same
  if(abs(dist(point_in_circle, circle_center) - 100) > 0.00000001){
    printf("Dist (validate point belongs to circle) diff with 100 %f: %f\n",abs(dist(point_in_circle, circle_center) - 100),dist(point_in_circle, circle_center));
    if(msg.size() > 0){
      cout << msg << endl;
    }
    throw runtime_error("");
  }
}

void validate_point_belongs_to_circle(p point_in_circle, p circle_center){
  validate_point_belongs_to_circle(point_in_circle, circle_center, string(""));
}


// The simple tangent calculated by moving the origin->origin distance vector
pair<pair<p, p>, bool> valid_tangent1_from_circle_to_circle(p circle1, p circle2, bool which, int excepting){
  p dist_vect = vector_diff(circle2, circle1);

  double modulo = dist(dist_vect);
  p norm = make_pair(dist_vect.first/modulo, dist_vect.second/modulo);

  if(abs(dist(norm) - 1) > 0.000000001){
    throw runtime_error("normalized vector does not have modulo 1");
  }

  p orig1 = circle1;
  p orig2 = circle2;

  if(which){
    circle1.first -= norm.second * R;
    circle1.second += norm.first * R;
    circle2.first -= norm.second * R;
    circle2.second += norm.first * R;
  } else {
    circle1.first += norm.second * R;
    circle1.second -= norm.first * R;
    circle2.first += norm.second * R;
    circle2.second -= norm.first * R;
  }
  if(line_intersects_any(circle1, circle2, excepting)){
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }

  validate_point_belongs_to_circle(circle1, orig1, "tangent getter");
  validate_point_belongs_to_circle(circle2, orig2, "tangent getter");

  return make_pair(make_pair(circle1, circle2), true);
}

p rotate_by_angle(p vect, double angle){
  double newX = vect.first * cos(angle) - vect.second * sin(angle);
  double newY = vect.first * sin(angle) + vect.second * cos(angle);
  return make_pair(newX, newY);
}

pair<pair<p, p>, bool> valid_tangent2_from_circle_to_circle(p circle1, p circle2, bool which, int excepting){
  if(dist(circle1, circle2) < (2 * R)/* - 0.0000001 MAYBE NOT NECESSARY*/){ // circles overlapping. This case cannot have a transverse tangent.
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }
  double angle = acos(2 * R/dist(circle1, circle2));
  p dist_vect = vector_diff(circle2, circle1);
  p orig1 = circle1;
  p orig2 = circle2;

  double modulo = dist(dist_vect);
  p norm = make_pair(dist_vect.first/modulo, dist_vect.second/modulo);

  if(abs(dist(norm) - 1) > 0.000000001){
    throw runtime_error("normalized vector does not have modulo 1");
  }

  p norm1 = norm;
  p norm2 = norm;

  if(abs(dist(norm1) - 1) > 0.000000001) throw runtime_error("normalized vector does not have modulo 1");
  if(abs(dist(norm2) - 1) > 0.000000001) throw runtime_error("normalized vector does not have modulo 1");


  if(which){
    norm1 = rotate_by_angle(norm1, angle);
    norm2 = rotate_by_angle(norm2, angle);
    //printf("norm1 vector %f %f\n", norm1.first, norm1.second);
    //printf("norm2 vector %f %f\n", norm2.first, norm2.second);
    circle1.first += norm1.first * R;
    circle1.second += norm1.second * R;
    circle2.first -= norm2.first * R;
    circle2.second -= norm2.second * R;
  } else {
    norm1 = rotate_by_angle(norm1, -angle);
    norm2 = rotate_by_angle(norm2, -angle);
    //printf("norm1 vector %f %f\n", norm1.first, norm1.second);
    //printf("norm2 vector %f %f\n", norm2.first, norm2.second);
    circle1.first += norm1.first * R;
    circle1.second += norm1.second * R;
    circle2.first -= norm2.first * R;
    circle2.second -= norm2.second * R;
  }

  // line intersects any circle?
  if(intersects(circle1, circle2, orig1)){
    cout << "intersects with circle 1" << endl;
  }
  if(intersects(circle1, circle2, orig2)){
    cout << "intersects with circle 2" << endl;
  }

  if(line_intersects_any(circle1, circle2, excepting)){
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }

  validate_point_belongs_to_circle(circle1, orig1, "tangent getter");
  validate_point_belongs_to_circle(circle2, orig2, "tangent getter");

  expect(err_eq(dist(make_pair(circle1, circle2)), tang2_length(dist(orig1, orig2))), 67899876);
  

  double dist_tang = dist(make_pair(circle1, circle2));
  double dist_circle_center = tang2_length(dist(orig1, orig2));


  if(!err_eq(dist_tang, dist_circle_center)){
    printf("Tan len: %f, dist: %f. Circles (%f, %f) & (%f, %f). Tan from (%f, %f) -> (%f, %f)\n", 
      dist_tang, dist_circle_center, orig1.first, orig1.second, orig2.first, orig2.second, 
      circle1.first, circle1.second, circle2.first, circle2.second);
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }
  return make_pair(make_pair(circle1, circle2), true);
}


double arc(p circle_center, p p1, p p2){
  validate_point_belongs_to_circle(p1, circle_center, "arc");
  validate_point_belongs_to_circle(p2, circle_center, "arc");

  double dx = circle_center.first - p1.first;
  double first = acos(dx/R);
  dx = circle_center.first - p2.first;
  double second = acos(dx/R);

  double angle_diff = abs(second - first);


  double xa = circle_center.first - p1.first;
  double ya = circle_center.second - p1.second;
  double xb = circle_center.first - p2.first;
  double yb = circle_center.second - p2.second;
  angle_diff = acos((xa * xb + ya * yb) / (sqrt(pow(xa, 2) + pow(ya, 2)) * sqrt(pow(xb, 2) + pow(yb, 2))));

  //printf("Angles %f , %f, diff %f\n", first, second, angle_diff);
  double arc_val = abs(angle_diff * R);
  const double total = 2 * PI * R;
  double diff_arc = total - arc_val;
  double ret = min(arc_val, diff_arc);

  if(ret > total || diff_arc > total){
    throw runtime_error("Arc or some other values are higher than full perimeter");
  }
  if(ret < 0){
    throw runtime_error("Arc is negative");
  }
  return ret;
}

bool all_visited(int visited){
  for(int i=0; i<N; i++){
    if((visited & (1 << i)) == 0)
      return false;
  }
  return true;
}

vector<pair<p,p>> curr_path;
vector<pair<p,p>> best_path;

vector<int> curr_path_idx;
vector<int> best_path_idx;

double ans = DBL_MAX;

double angle_between_vectors(p v1, p v2){
  double x1 = v2.first;
  double y1 = v2.second;
  double x2 = v1.first;
  double y2 = v1.second;
  return atan2((x1*y2)-(y1*x2), (x1*x2)+(y1*y2));
  double top = (v1.first * v2.first) + (v1.second * v2.second);
  double bottom = dist(v1) * dist(v2);
  return acos(top/bottom);
}

double path(int pole_id, p point_in_circle, double accum, int visited_poles, pair<p,p> incoming_line){
  pair<pair<p, p>, bool> res1 = valid_line_from_point_to_circle_border(goal, poles[pole_id], false, visited_poles);
  pair<pair<p, p>, bool> res2 = valid_line_from_point_to_circle_border(goal, poles[pole_id], true, visited_poles);
  if(accum > ans) return accum;
  vector<pair<p, p>> res;
  if(res1.second) res.push_back(res1.first);
  if(res2.second) res.push_back(res2.first);
  bool bad = false;
  expect(res.size() <= 2, 3);

  for(int i=0; i<res.size(); i++){
    pair<p, p> line = res[i];
    p g = line.first;
    p in_circle = line.second;

    if(g.first != goal.first || g.second != goal.second){
      throw runtime_error("we are getting line from goal but the first point is not goal");
    }

    validate_point_belongs_to_circle(point_in_circle, poles[pole_id], "when getting direct access to goal");
    validate_point_belongs_to_circle(in_circle, poles[pole_id], "when getting direct access to goal");
    double result = accum + arc(poles[pole_id], point_in_circle, in_circle) + dist(line);
    
    p one = vector_diff(point_in_circle, poles[i]);
    p third = vector_diff(in_circle, poles[i]);

    for(int j=0; j<N; j++){
      if(i == j) continue;
      if(dist(vector_diff(poles[j], poles[i])) < R*2){
        p two = vector_diff(poles[j], poles[i]);
        if(angle_between_vectors(one, two) <= angle_between_vectors(one, third)){
          bad = true;
          break;
        }
      }
    }

    if(!bad && result < ans) {
      ans = result;
    }
  }

  /*
  if(!bad && !res.empty()){

    best_path = curr_path;
    best_path_idx = curr_path_idx;
    if(res.size() > 0){
      auto xx = res[1];
      auto temp = xx.second;
      xx.second = xx.first;
      xx.first = temp;
      best_path.push_back(xx);
    }
    for(int z=0; z<res.size(); z++){
      pair<p,p> pair;
      pair.first = res[z].second;
      pair.second = res[z].first;
    }
  }*/

  validate_point_belongs_to_circle(point_in_circle, poles[pole_id], "first point in path");

  for(int i=0; i<N; i++){
    if((visited_poles & (1 << i)) != 0) continue;
    double new_visited_poles = visited_poles | (1 << i);

    vector<pair<p,p>> lines;

    for(int b=0; b<2; b++){
      auto res1 = valid_tangent1_from_circle_to_circle(poles[pole_id], poles[i], bools[b], new_visited_poles /* OR new_visited_poles */);
      auto res2 = valid_tangent2_from_circle_to_circle(poles[pole_id], poles[i], bools[b], new_visited_poles /* OR new_visited_poles */);
      if(res1.second) lines.push_back(res1.first);
      if(res2.second) lines.push_back(res2.first);
    }

    for(auto line : lines){
      validate_point_belongs_to_circle(line.first, poles[pole_id], "first point from tangent");
      validate_point_belongs_to_circle(line.second, poles[i], "second point from tangent");
      bool bad = false;

      p one = vector_diff(point_in_circle, poles[i]);
      p third = vector_diff(line.first, poles[i]);

      for(int j=0; j<N; j++){
        if(i == j) continue;
        if(dist(vector_diff(poles[j], poles[i])) < R*2){
          p two = vector_diff(poles[j], poles[i]);
          if(angle_between_vectors(one, two) <= angle_between_vectors(one, third)){
            bad = true;
            break;
          }
        }
      }
      if(bad) continue;

      curr_path.push_back(line);
      curr_path_idx.push_back(i);
      double result = path(i, line.second, accum + arc(poles[pole_id], point_in_circle, line.first) + dist(line), new_visited_poles, line);
      curr_path.pop_back();
      curr_path_idx.pop_back();
      if(result < ans) ans = result;
    }
  }

  return ans;
}

// Go style with errors lol
pair<pair<p, p>, bool> valid_line_from_point_to_circle_border(p p1, p circle_center, bool which, int excepting){
  p dist_vect = vector_diff(circle_center, p1);
  p tangent;
  double d = dist(dist_vect);
  double alpha = asin(R / d);
  double length = sqrt((d * d) - (R*R));

  
  if(which){
    tangent = rotate_by_angle(dist_vect, alpha);
  } else {
    tangent = rotate_by_angle(dist_vect, -alpha);
  }
  
  // Normalize
  double tangent_modulo = dist(tangent);
  tangent = make_pair(tangent.first/tangent_modulo, tangent.second/tangent_modulo);

  if(abs(dist(tangent) - 1) > 0.000000001){
    throw runtime_error("normalized vector does not have modulo 1");
  }

  // Amplify so that it reaches to points
  tangent = make_pair(tangent.first*length, tangent.second*length);

  tangent = make_pair(tangent.first + p1.first, tangent.second + p1.second);

  p target_point = tangent;

  validate_point_belongs_to_circle(target_point, circle_center, "haha");
  //if(target_point.first == 0 && target_point.second == 0) throw runtime_error("first point of line (from robot) is not 0,0");

  bool bad = false;

  for(int i=0; i<N; i++){
    if(dist(vector_diff(p1, poles[i])) < R) bad = true;
  }

  if(bad || line_intersects_any(p1, target_point, excepting)){
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }

  return make_pair(make_pair(p1, target_point), true);
}

void solve(){
  ans = DBL_MAX;
  for(int i=0; i<N; i++){
    double x, y;
    scanf("%le %le", &x, &y);
    poles[i] = make_pair(x, y);
  }
  bool intersection = false;
  for(int i=0; i<N; i++){
    if(intersects(make_pair(0, 0), goal, poles[i])){
      intersection = true;
      break;
    }
  }
  if(!intersection){
    printf("%0.5f\n", dist(make_pair(0, 0), goal));
    return;
  }

  double ans = DBL_MAX;
  for(int i=0; i<N; i++){
    int excepting = (1<<i);

    for(int K=0; K<2; K++){
      bool b = bools[K];

      pair<pair<p,p>, bool> res = valid_line_from_point_to_circle_border(make_pair(0,0), poles[i], b, 0);


      if(res.second){
        pair<p,p> line = res.first;
        if(i == 5 && b){
          //printf("Line from (0,0) to pole 5: ");
          //print_line(res.first);
          if(line_intersects_any(line.first, line.second, 0)){
            cout << "wtf" << endl;
          }
        }

              
        //fprintf(stderr, "Trying line (valid: %d): ", 1);
        //print_line(line);
        //fprintf(stderr, "\n");
        
        curr_path.push_back(line);
        curr_path_idx.push_back(i);
        double length = path(i, line.second, dist(line), excepting, line);
        curr_path.pop_back();
        curr_path_idx.pop_back();
        if(length < ans) ans = length;
        //cerr << "backtrack" << endl;
      }
    }
  }

  cerr << "path:" << endl;
  for(auto line : best_path){
    print_line(line);
  }

  cerr << endl;
  cerr << "path (POLE ID):" << endl;
  for(int pole_id : best_path_idx){
    cerr << pole_id << " ";
  }cerr << endl;

  if(ans == DBL_MAX){
    printf("0.0\n");
  } else {
    printf("%0.5f\n", ans);
  }
}


void test_intersects(){
  expect(!intersects(make_pair(-50, 100), make_pair(50, 100), make_pair(0, 0)), 0);
  expect(intersects(make_pair(-50, 100), make_pair(50, 99.9999999), make_pair(0, 0)), 0);
  expect(intersects(make_pair(-5, 5), make_pair(5, -5), make_pair(0, 0)), 0);
  expect(intersects(make_pair(-50, 95), make_pair(50, 95), make_pair(0, 0)), 0);
  expect(intersects(make_pair(-50, -100), make_pair(50, -99.9999999), make_pair(0, 0)), 0);
  expect(!intersects(make_pair(-50, -100), make_pair(50, -100), make_pair(0, 0)), 0);
  expect(!intersects(make_pair(0, 101), make_pair(3, 150), make_pair(0, 0)), 100);
  expect(!intersects(make_pair(3, 150), make_pair(0, 101), make_pair(0, 0)), -100);
  expect(!intersects(make_pair(0, 101), make_pair(3, 150), make_pair(0, 0)), 101);
  expect(intersects(make_pair(0, 150), make_pair(0, 99.99999999), make_pair(0, 0)), 1022);
  expect(!intersects(make_pair(0, 150), make_pair(0, 100.000001), make_pair(0, 0)), 1022);
  expect(!intersects(make_pair(0, 150), make_pair(0, 100), make_pair(0, 0)), 102);
  expect(!intersects(make_pair(0, 150), make_pair(0, 100.00001), make_pair(0, 0)), 1023);
  expect(intersects(make_pair(0, 150), make_pair(0, 99.99999999), make_pair(0, 0)), 103);
  expect(intersects(make_pair(0, 99.99999999), make_pair(0, 150), make_pair(0, 0)), 104);
  expect(!intersects(make_pair(0, 100), make_pair(0, 150), make_pair(0, 0)), 105);
  expect(intersects(make_pair(0, 99.99999999), make_pair(0, 150), make_pair(0, 0)), 106);
  expect(intersects(make_pair(0, 0), make_pair(0, 150), make_pair(0, 0)), 106);
  expect(intersects(make_pair(-15000, 0), make_pair(0, 0), make_pair(0, 0)), 106);
  expect(intersects(make_pair(0, 0), make_pair(0, 0), make_pair(0, 0)), 106);
  expect(!intersects(make_pair(0, 99.999999999), make_pair(0, 150), make_pair(0, 0)), 107); // Does not intersect, because of error.
}



void test_tangent1(){
  auto line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(0, 200), true, 0);
  expect(line_eq(line.first, make_pair(make_pair(-100, 0), make_pair(-100, 200))), 0);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(0, 200), false, 0);
  expect(line_eq(line.first, make_pair(make_pair(100, 0), make_pair(100, 200))), 1);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(200, 0), true, 0);
  expect(line_eq(line.first, make_pair(make_pair(0, 100), make_pair(200, 100))), 2);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(200, 0), false, 0);
  expect(line_eq(line.first, make_pair(make_pair(0, -100), make_pair(200, -100))), 3);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(0, -200), true, 0);
  expect(line_eq(line.first, make_pair(make_pair(100, 0), make_pair(100, -200))), 4);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(0, -200), false, 0);
  expect(line_eq(line.first, make_pair(make_pair(-100, 0), make_pair(-100, -200))), 5);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(-200, 0), true, 0);
  expect(line_eq(line.first, make_pair(make_pair(0, -100), make_pair(-200, -100))), 6);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(-200, 0), false, 0);
  expect(line_eq(line.first, make_pair(make_pair(0, 100), make_pair(-200, 100))), 7);

  double n = R * cos(PI/4);
  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(200, 200), true, 0);
  expect(line_eq(line.first, make_pair(make_pair(-n, n), make_pair(200-n, 200+n))), 8);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(500, 500), false, 0);
  expect(line_eq(line.first, make_pair(make_pair(n, -n), make_pair(500+n, 500-n))), 9);

  line = valid_tangent1_from_circle_to_circle(make_pair(0, 0), make_pair(50, 50), false, 0); // Circle inside another one (OK)
  expect(line_eq(line.first, make_pair(make_pair(n, -n), make_pair(50+n, 50-n))), 10);
}


void test_tangent2(){
  // Test using the internal validator:
  pair<pair<p,p>, bool> line;
  pair<p,p> l1 = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(1000, 0), false, 0).first;
  pair<p,p> l2 = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(1000, 0), true, 0).first;
  // Check the two tangents are not same
  expect(l1.first != l2.first, 0);
  expect(l1.second != l2.second, 1);
  for(int i=0; i<2; i++){
    auto x = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(1000, 0), bools[i], 0); expect(x.second, 23); // ALL VALID
    x = valid_tangent2_from_circle_to_circle(make_pair(2, 5), make_pair(1000, 0), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(-30, 40), make_pair(1000, 0), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(230, 45), make_pair(879, -40), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(10, 0), make_pair(1000, 2), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(20, 4), make_pair(1000, 34), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(10, 0), make_pair(876, -40), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(240, 4), make_pair(845, 0), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(845, 0), make_pair(240, 4), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(-10, 0), make_pair(340, 25), bools[i], 0); expect(x.second, 23);
    x = valid_tangent2_from_circle_to_circle(make_pair(-240, 4), make_pair(500, 4), bools[i], 0); expect(x.second, 23);
  }

  line = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(200, 0), true, 0);
  line = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(500, 0), true, 0);
  line = valid_tangent2_from_circle_to_circle(make_pair(0, 0), make_pair(1000, 0), true, 0);
  expect(err_eq(dist(line.first), tang2_length(1000)), 0);


  // For this tangent, you cannot have circles that are inside each other. But for the belt tangents (the ones that are not crossed
  // you can have them even in that situation.)
  expect(!valid_tangent2_from_circle_to_circle(make_pair(80, -100), make_pair(80, 80), true, 0).second, 34);
  expect(!valid_tangent2_from_circle_to_circle(make_pair(80, -100), make_pair(80, 80), false, 0).second, 35);
  expect(valid_tangent2_from_circle_to_circle(make_pair(80, -100), make_pair(80+200, -100), false, 0).second, 36);
}

void test_arc(){
  // Works nice ;)
  expect(arc(make_pair(0, 0), make_pair(-100, 0), make_pair(100, 0)) == PI * R, 0);
  expect(arc(make_pair(0, 0), make_pair(-100, 0), make_pair(0, 100)) == PI * R/2, 0);
  expect(arc(make_pair(0, 0), make_pair(-100, 0), make_pair(0, -100)) == PI * R/2, 0);
  double n = R * cos(PI/4);
  expect(arc(make_pair(0, 0), make_pair(-100, 0), make_pair(-n, n)) == PI * R/4, 4);
  expect(arc(make_pair(0, 0), make_pair(-n, n), make_pair(-100, 0)) == PI * R/4, 4);
  expect(arc(make_pair(0, 0), make_pair(-n, n), make_pair(n, -n)) == PI * R, 4);
  expect(arc(make_pair(0, 0), make_pair(0, 100), make_pair(n, -n)) == (PI/2 + PI/4) * R, 4);
  expect(arc(make_pair(0, 0), make_pair(n, -n), make_pair(0, 100)) == (PI/2 + PI/4) * R, 4);
}

void test_rotate_by_angle(){
  p rotated;
  rotated = rotate_by_angle(make_pair(2, 0), PI/2);
  expect(err_eq(rotated.first, 0) && err_eq(rotated.second, 2), 1000);
  rotated = rotate_by_angle(make_pair(0, 2), PI/2);
  expect(err_eq(rotated.first, -2) && err_eq(rotated.second, 0), 1001);
  rotated = rotate_by_angle(make_pair(-2, 0), PI/2);
  expect(err_eq(rotated.first, 0) && err_eq(rotated.second, -2), 1002);
}

void test_valid_line_from_point_to_circle_border(){
  auto line = valid_line_from_point_to_circle_border(make_pair(0, 0), make_pair(100, 100), false, 0).first;
  expect(line.first.first == 0, 1);
  expect(line.first.second == 0, 2);
  expect(line.second.first == 100, 3);
  expect(err_eq(line.second.second, 0), 4);

  line = valid_line_from_point_to_circle_border(make_pair(0, 0), make_pair(100, 100), true, 0).first;
  expect(line.first.first == 0, 1);
  expect(line.first.second == 0, 2);
  expect(err_eq(line.second.first, 0), 3);
  expect(err_eq(line.second.second, 100.000000), 4);
}

int main(){
  N = 0;
  // Tests
  
  test_rotate_by_angle();
  test_intersects();
  test_tangent1();
  test_tangent2();
  test_arc();
  test_valid_line_from_point_to_circle_border();
  //return 0;
  double gx, gy;
  while(scanf("%d %le %le", &N, &gx, &gy) == 3){
    goal = make_pair(gx, gy);
    solve();
  }
}
