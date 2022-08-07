use std::collections::BinaryHeap;
use std::io::{self, BufRead};

fn read_line() -> String {
  io::stdin().lock().lines().next().unwrap().unwrap()
}

fn read_nums() -> Vec<i32> {
  read_line()
    .split(' ')
    .map(|x| x.trim().parse::<i32>().unwrap())
    .collect()
}

static DI: [i32; 4] = [-1, 1, 0, 0];
static DJ: [i32; 4] = [0, 0, -1, 1];

fn main() {
  let size = read_nums();
  let m = size[0] as usize;
  let n = size[1] as usize;

  let matrix: Vec<Vec<i32>> = (0..m).map(|_| read_nums()).collect();

  let mut dist = vec![vec![i32::MAX; n]; m];

  let mut q = BinaryHeap::<(i32, usize, usize)>::new();

  q.push((0, 0, 0));
  dist[0][0] = 0;

  while !q.is_empty() {
    let (_, i, j) = q.pop().unwrap();

    for d in 0..4 {
      if (i == 0 && DI[d] == -1) || (j == 0 && DJ[d] == -1) {
        continue;
      }

      let i2 = ((i as i32) + DI[d]) as usize;
      let j2 = ((j as i32) + DJ[d]) as usize;

      if i2 >= m || j2 >= n {
        continue;
      }

      let height = i32::max(0, matrix[i2][j2] - matrix[i][j]);
      let alt = i32::max(dist[i][j], height);

      if alt < dist[i2][j2] {
        dist[i2][j2] = alt;
        q.push((-alt, i2, j2));
      }
    }
  }

  println!("{}", dist[m - 1][n - 1]);
}
