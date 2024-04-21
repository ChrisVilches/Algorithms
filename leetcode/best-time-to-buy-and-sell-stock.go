func maxProfit(prices []int) int {
	minVal := prices[0]
	ans := 0

	for _, p := range prices {
		ans = max(ans, p-minVal)
		minVal = min(minVal, p)
	}

	return ans
}
