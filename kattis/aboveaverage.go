package main

import "fmt"

func main() {
	var C int
	fmt.Scan(&C)

	for c := 0; c < C; c++ {
		var N int
		fmt.Scan(&N)

		grades := make([]float64, N)

		avg := 0.0

		for i := 0; i < N; i++ {
			fmt.Scan(&grades[i])
			avg += grades[i]
		}

		avg /= float64(N)

		above := 0

		for i := 0; i < N; i++ {
			if grades[i] > avg {
				above++
			}
		}

		fmt.Printf("%.3f%%\n", 100*float64(above)/float64(N))
	}
}
