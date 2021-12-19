package main

import (
	"fmt"
	"io"
)

func print(n int) {
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			if i == n-j-1 {
				fmt.Print(2)
			} else if i == j {
				fmt.Print(1)
			} else {
				fmt.Print(3)
			}
		}
		fmt.Println()
	}
}

func main() {
	var n int

	for {
		_, err := fmt.Scan(&n)
		if err == io.EOF {
			break
		}

		print(n)
	}
}
