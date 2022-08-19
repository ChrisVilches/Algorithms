package main

func twoSum(nums []int, target int) []int {

	idx := make(map[int]int)

	for i, n := range nums {
		idx[n] = i
	}

	for i, a := range nums {
		b := target - a

		j, ok := idx[b]

		if !ok || i == j {
			continue
		}

		return []int{i, j}
	}

	return []int{}
}
