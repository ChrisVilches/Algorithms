package main

import "fmt"

func main() {
	digitMap := []int{0, 1, 2, 5, 9, 8, 6}

	var n int

	for {
		_, err := fmt.Scan(&n)

		if err != nil {
			break
		}

		for n > 0 {
			fmt.Print(digitMap[n%7])
			n /= 7
		}

		fmt.Println()
	}
}
