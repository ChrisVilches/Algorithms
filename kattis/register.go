package main

import (
	"fmt"
)

var primes = []int{2, 3, 5, 7, 11, 13, 17, 19}

func main() {
	nums := make([]int, 8)

	for i := range nums {
		fmt.Scan(&nums[i])
	}

	total := 1
	curr := 1

	for i := range primes {
		curr += nums[i] * total
		total *= primes[i]
	}

	fmt.Println(total - curr)
}
