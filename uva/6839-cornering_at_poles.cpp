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

pair<pair<p,p>,bool> valid_line_from_point_to_circle_border(p p1, p circle_center, bool which, int excepting);
constexpr auto eps = 1e-14;



double dist(p p1, p p2){
  double a = p1.first - p2.first;
  double b = p1.second - p2.second;
  return sqrt((a*a) + (b*b));
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

// The simple tangent calculated by moving the origin->origin distance vector
pair<pair<p, p>, bool> valid_tangent1_from_circle_to_circle(p circle1, p circle2, bool which, int excepting){
  p dist_vect = vector_diff(circle2, circle1);

  double modulo = dist(dist_vect);
  p norm = make_pair(dist_vect.first/modulo, dist_vect.second/modulo);

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

  p norm1 = norm;
  p norm2 = norm;

  if(which){
    norm1 = rotate_by_angle(norm1, angle);
    norm2 = rotate_by_angle(norm2, angle);
    circle1.first += norm1.first * R;
    circle1.second += norm1.second * R;
    circle2.first -= norm2.first * R;
    circle2.second -= norm2.second * R;
  } else {
    norm1 = rotate_by_angle(norm1, -angle);
    norm2 = rotate_by_angle(norm2, -angle);
    circle1.first += norm1.first * R;
    circle1.second += norm1.second * R;
    circle2.first -= norm2.first * R;
    circle2.second -= norm2.second * R;
  }

  if(line_intersects_any(circle1, circle2, excepting)){
    p zero = make_pair(0, 0);
    pair<p, p> empty_line = make_pair(zero, zero);
    return make_pair(empty_line, false);
  }

  return make_pair(make_pair(circle1, circle2), true);
}

double angle_between_vectors(p v1, p v2){
  double x1 = v2.first;//refactor names lol
  double y1 = v2.second;
  double x2 = v1.first;
  double y2 = v1.second;

  return atan2((x1*y2)-(y1*x2), (x1*x2)+(y1*y2));
}

double arc(p circle_center, p p1, p p2){

  double haha = angle_between_vectors(vector_diff(p1, circle_center), vector_diff(p2, circle_center)) * R;

  return abs(haha);

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
  double arc_val = angle_diff * R;
  return arc_val;
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

double ans = DBL_MAX;

void print_line(pair<p,p> line){
  fprintf(stderr, "Line: (%f, %f) ---> (%f, %f)\n", line.first.first, line.first.second, line.second.first, line.second.second);
}

double path(int pole_id, p point_in_circle, double accum, int visited_poles, pair<p,p> incoming_line){
  pair<pair<p, p>, bool> res1 = valid_line_from_point_to_circle_border(goal, poles[pole_id], false, visited_poles);
  pair<pair<p, p>, bool> res2 = valid_line_from_point_to_circle_border(goal, poles[pole_id], true, visited_poles);
  if(accum > ans) return accum;
  vector<pair<p, p>> res;
  if(res1.second) res.push_back(res1.first);
  if(res2.second) res.push_back(res2.first);
  bool bad = false;

  for(int i=0; i<res.size(); i++){
    pair<p, p> line = res[i];
    p g = line.first;
    p in_circle = line.second;

    if(g.first != goal.first || g.second != goal.second){
      throw runtime_error("we are getting line from goal but the first point is not goal");
    }

    double arc_dist = arc(poles[pole_id], point_in_circle, in_circle);
    //arc_dist = (PI * R) - arc_dist; // YOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO THIS WORKS!!!!!!!!!!!!!!!!!!
    
    double result = accum + arc_dist + dist(line);

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
/*
    fprintf(stderr, "Lines (GOOD=%d), incoming line (arc here), tangent leaving the circle towards goal:\n", !bad);
    print_line(incoming_line);
    pair<p,p> gl;
    gl.first = line.second;
    gl.second = line.first;
    print_line(gl);
    fprintf(stderr, "Accum length of this route: %f\n\n", result);*/

    if((arc_dist >= 0) && !bad && result < ans) {
      ans = result;
    }
  }

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

      double arc_dist = arc(poles[pole_id], point_in_circle, line.first);
      if(arc_dist >= 0){
        double result = path(i, line.second, accum + arc_dist + dist(line), new_visited_poles, line);
        if(result < ans) ans = result;
      }
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
        double length = path(i, line.second, dist(line), excepting, line);
        if(length < ans) ans = length;
      }
    }
  }

  if(ans == DBL_MAX){
    printf("0.0\n");
  } else {
    printf("%0.5f\n", ans);
  }
}

int main(){
  double gx, gy;
  while(scanf("%d %le %le", &N, &gx, &gy) == 3){
    goal = make_pair(gx, gy);
    solve();
  }
}
