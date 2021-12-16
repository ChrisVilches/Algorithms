package main

import (
	"fmt"
)

func main() {
	var N int

	fmt.Scan(&N)

	curr_time := 0
	total := 0

	if N%2 == 1 {
		fmt.Printf("still running\n")
		return
	}

	for i := 0; i < N; i++ {
		prev_time := curr_time

		fmt.Scan(&curr_time)

		if i%2 == 1 {
			total += curr_time - prev_time
		}
	}

	fmt.Printf("%d\n", total)
}
