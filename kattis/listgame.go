package main

import (
	"fmt"
)

func main() {
	var x int
	fmt.Scan(&x)

	k := 0

	for x > 1 {
		factor := -1

		for i := 2; i*i <= x; i++ {
			if x%i == 0 {
				factor = i
				break
			}
		}

		k++
		x /= factor
	}

	fmt.Println(k)
}
