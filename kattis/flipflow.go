package main

import (
	"fmt"
	"io"
)

func main() {
	var t, s, n int

	for {
		_, err := fmt.Scan(&t, &s, &n)

		if err == io.EOF {
			break
		}

		times := make([]int, n+1)

		for i := 0; i < n; i++ {
			fmt.Scan(&times[i])
		}

		times[n] = t
		curr := s

		for i := 0; i < n; i++ {
			curr = s - curr

			curr += times[i+1] - times[i]

			if curr > s {
				curr = s
			}
		}

		fmt.Println(s - curr)
	}
}
