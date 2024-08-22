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

		digits := []int{}

		for n > 0 {
			digits = append(digits, digitMap[n%7])
			n /= 7
		}

		for _, d := range digits {
			fmt.Print(d)
		}

		fmt.Println()
	}
}
