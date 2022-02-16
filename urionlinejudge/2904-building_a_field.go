package main

import "fmt"

var (
	nums        [100001]int
	N           int
	totalLength int
)

func possible() bool {
	if totalLength%2 != 0 {
		return false
	}

	half := totalLength / 2
	partitions := 0
	curr := nums[0]
	j := 1

	for i := 0; i < N; i++ {
		for ; j < N; j++ {
			if curr == half {
				partitions++
			}

			if curr >= half {
				break
			}

			curr += nums[j]

		}
		curr -= nums[i]
	}

	return partitions >= 2
}

func main() {
	fmt.Scan(&N)

	totalLength = 0

	for i := 0; i < N; i++ {
		fmt.Scan(&nums[i])
		totalLength += nums[i]
	}

	if possible() {
		fmt.Println("Y")
	} else {
		fmt.Println("N")
	}
}
