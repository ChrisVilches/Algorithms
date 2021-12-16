package main

import (
	"fmt"
)

func main() {
	var N int
	var days [370]bool

	fmt.Scan(&N)

	for i := 0; i < N; i++ {
		var s, t int
		fmt.Scan(&s, &t)

		for ; s <= t; s++ {
			days[s] = true
		}
	}

	total := 0

	for i := 0; i < 370; i++ {
		if days[i] {
			total++
		}
	}

	fmt.Printf("%d\n", total)
}
