use std::collections::HashSet;

fn digits(mut n: i32) -> Vec<i32> {
  let mut result = vec![];

  loop {
    result.push(n % 10);
    n /= 10;
    if n == 0 {
      break;
    }
  }

  result
}

fn process(n: i32) -> i32 {
  let dig = digits(n);
  let mut sum = 0;

  for value in dig {
    sum += value * value;
  }

  sum
}

impl Solution {
  pub fn is_happy(mut n: i32) -> bool {
    let mut present: HashSet<i32> = HashSet::new();

    while n != 1 {
      if present.contains(&n) {
        return false;
      }

      present.insert(n);

      n = process(n);
    }

    true
  }
}
