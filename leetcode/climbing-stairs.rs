impl Solution {
  pub fn climb_stairs(n: i32) -> i32 {
    let mut dp = vec![0; 50];
    dp[0] = 1;
    dp[1] = 1;

    for i in 2..48 {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    dp[n as usize]
  }
}
