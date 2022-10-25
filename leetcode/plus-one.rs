impl Solution {
  pub fn plus_one(digits: Vec<i32>) -> Vec<i32> {
    let mut result = vec![0];

    result.append(&mut digits.clone());

    let mut idx = result.len() - 1;

    loop {
      result[idx] += 1;

      if result[idx] <= 9 {
        break;
      }

      result[idx] = 0;
      idx -= 1;
    }

    if result[0] == 0 {
      result.remove(0);
    }

    result
  }
}
