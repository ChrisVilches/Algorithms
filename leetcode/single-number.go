package main

func singleNumber(nums []int) int {
	freq := make(map[int]int)

	for _, n := range nums {
		freq[n]++
	}

	for num, freq := range freq {
		if freq == 1 {
			return num
		}
	}

	return 0
}
