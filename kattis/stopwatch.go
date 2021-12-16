package main

import (
	"fmt"
)

func main() {
	var N int

	fmt.Scan(&N)

	currTime := 0
	total := 0

	if N%2 == 1 {
		fmt.Printf("still running\n")
		return
	}

	for i := 0; i < N; i++ {
		prevTime := currTime

		fmt.Scan(&currTime)

		if i%2 == 1 {
			total += currTime - prevTime
		}
	}

	fmt.Printf("%d\n", total)
}
