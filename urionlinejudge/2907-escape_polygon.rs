use std::io;

fn read_line() -> String {
  let mut line = String::new();
  io::stdin().read_line(&mut line).unwrap();
  line
}

fn read_int() -> i32 {
  read_line().trim().parse().unwrap()
}

fn read_point() -> Point {
  let line = read_line();
  let nums: Vec<&str> = line.split(' ').collect();

  Point {
    x: nums[0].trim().parse().unwrap(),
    y: nums[1].trim().parse().unwrap(),
  }
}

#[derive(Clone, Copy)]
struct Point {
  x: i64,
  y: i64,
}

impl Point {
  fn to(&self, p: &Point) -> Point {
    Point {
      x: p.x - self.x,
      y: p.y - self.y,
    }
  }

  fn cross(&self, p: &Point) -> i64 {
    self.x * p.y - self.y * p.x
  }
}

fn tetrahedral_number(n: i64) -> i64 {
  n * (n + 1) * (n + 2) / 6
}

fn triangular_number(n: i64) -> i64 {
  n * (n + 1) / 2
}

fn count(n: usize, points: &Vec<Point>) -> i64 {
  let mut ans = tetrahedral_number((n - 2) as i64);

  for i in 0..n {
    let vec1: Point = points[i].to(&points[i + 1]);

    let mut lo = i + 1;
    let mut hi = n + i - 1;

    while lo < hi {
      let mid = (lo + hi) / 2;

      let vec2: Point = points[mid].to(&points[mid + 1]);

      if vec1.cross(&vec2) >= 0 {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    ans -= triangular_number((lo - i - 2) as i64);
  }

  ans
}

fn main() {
  let n = read_int() as usize;
  let mut points = Vec::<Point>::new();

  for _ in 0..n {
    points.push(read_point());
  }

  for i in 0..n {
    points.push(points[i]);
  }

  println!("{}", count(n, &points));
}
