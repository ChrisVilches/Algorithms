use std::io::{self, BufRead};

fn read_line() -> String {
  io::stdin().lock().lines().next().unwrap().unwrap()
}

fn read_nums() -> Vec<f32> {
  read_line()
    .split(' ')
    .map(|x| x.trim().parse::<f32>().unwrap())
    .collect()
}

fn main() {
  let nums: Vec<f32> = read_nums();

  let x1 = f32::min(nums[0], nums[2]);
  let y1 = f32::min(nums[1], nums[3]);

  let x2 = f32::max(nums[0], nums[2]);
  let y2 = f32::max(nums[1], nums[3]);

  let area = ((x1 - x2) * (y1 - y2)).abs();

  println!("{:.5}", area);
}
