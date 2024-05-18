func c2(n int) int {
	return n * (n - 1) / 2
}

func numIdenticalPairs(nums []int) int {
	counts := make(map[int]int)

	for _, x := range nums {
		counts[x]++
	}

	result := 0

	for _, count := range counts {
		result += c2(count)
	}

	return result
}
