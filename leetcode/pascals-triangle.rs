impl Solution {
  pub fn generate(num_rows: i32) -> Vec<Vec<i32>> {
    let mut result = vec![vec![1]];

    for row_idx in 1..num_rows {
      let mut row = vec![1];
      let prev_row = result.last().unwrap();

      for i in 0..prev_row.len() - 1 {
        row.push(prev_row[i] + prev_row[i + 1]);
      }

      row.push(1);
      result.push(row);
    }

    result
  }
}
