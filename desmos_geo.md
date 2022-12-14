# Visualize geometric shapes using desmos

```c++
struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  // ...
  string to_desmos() const {
    stringstream ss;
    ss << fixed << setprecision(6) << "\\left(\\left(1-t\\right)\\cdot" << p.x
       << "+t\\cdot" << q.x << ",\\left(1-t\\right)\\cdot" << p.y << "+t\\cdot" << q.y
       << "\\right)";
    return ss.str();
  }
};
```

```c++
struct Circle {
  Point center;
  ld radius;
  Circle(Point c, ld r) : center(c), radius(r) {}
  // ...
  string to_desmos() const {
    stringstream ss;
    ss << "\\left(x-" << center.x << "\\right)^{2}+\\left(y-" << center.y
       << "\\right)^{2}=" << radius << "^{2}";
    return ss.str();
  }
```

```c++
string polygon_to_str(const vector<Point>& polygon) {
  stringstream ss;
  ss << fixed << setprecision(6);
  ss << "polygon(";
  for (int i = 0; i < (int)polygon.size(); i++) {
    if (i > 0) ss << ", ";
    ss << "(" << polygon[i].x << ", " << polygon[i].y << ")";
  }
  ss << ")";
  return ss.str();
}
```

Print several objects using `cerr << my_segment.to_desmos() << endl;`, then paste (multiple lines at once is allowed) on https://www.desmos.com/calculator?lang=ja
