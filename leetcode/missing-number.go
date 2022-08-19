package main

func missingNumber(nums []int) int {
	present := make(map[int]struct{})

	for _, n := range nums {
		present[n] = struct{}{}
	}

	n := len(nums) + 1

	for i := 0; i < n; i++ {
		_, exists := present[i]

		if !exists {
			return i
		}
	}

	return 0
}
