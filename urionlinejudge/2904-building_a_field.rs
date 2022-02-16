use std::io;

fn read_line() -> String {
  let mut line = String::new();
  io::stdin().read_line(&mut line).unwrap();
  line
}

fn read_int() -> i32 {
  read_line().trim().parse().unwrap()
}

fn read_ints_line() -> Vec<i32> {
  read_line()
    .split(' ')
    .map(|x| x.trim().parse().unwrap())
    .collect()
}

fn possible(nums: &Vec<i32>) -> bool {
  let total_length: i32 = nums.iter().sum();

  if total_length % 2 != 0 {
    return false;
  }

  let half = total_length / 2;
  let mut partition_found = false;
  let mut curr = nums[0];
  let mut j = 1;

  for i in 0..nums.len() {
    while j < nums.len() {
      if curr == half {
        if partition_found {
          return true;
        }
        partition_found = true;
      }

      if curr >= half {
        break;
      }

      curr += nums[j];
      j += 1;
    }
    curr -= nums[i];
  }

  false
}

fn main() {
  let _ = read_int();
  let nums: Vec<i32> = read_ints_line();
  println!("{}", if possible(&nums) { 'Y' } else { 'N' });
}
