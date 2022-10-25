fn count_row(row: &Vec<i32>) -> i32 {
  let mut result = 0;

  for i in 0..row.len() - 1 {
    if row[i] != row[i + 1] {
      result += 1;
    }
  }

  if *row.first().unwrap() == 1 {
    result += 1;
  }

  if *row.last().unwrap() == 1 {
    result += 1;
  }
  result
}

fn count(grid: &Vec<Vec<i32>>) -> i32 {
  grid.iter().fold(0, |acc, row| acc + count_row(row))
}

fn rotate(grid: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
  let mut result = vec![];
  let rows = grid.len();
  let cols = grid.first().unwrap().len();

  for j in (0..cols).rev() {
    result.push(vec![]);
    for i in 0..rows {
      result.last_mut().unwrap().push(grid[i][j]);
    }
  }
  result
}

impl Solution {
  pub fn island_perimeter(grid: Vec<Vec<i32>>) -> i32 {
    count(&grid) + count(&rotate(&grid))
  }
}
