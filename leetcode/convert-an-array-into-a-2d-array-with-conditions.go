func findMatrix(nums []int) [][]int {
	result := [][]int{}

	counts := make(map[int]int)

	for _, x := range nums {
		counts[x]++
	}

	for len(counts) > 0 {
		curr := []int{}
		for key, _ := range counts {
			curr = append(curr, key)
			counts[key]--

			if counts[key] == 0 {
				delete(counts, key)
			}
		}

		result = append(result, curr)
	}

	return result
}
