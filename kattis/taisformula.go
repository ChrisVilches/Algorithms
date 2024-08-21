package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var n int
	fmt.Fscan(reader, &n)

	x := make([]float64, n)
	y := make([]float64, n)

	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &x[i], &y[i])
	}

	var area float64 = 0

	for i := 0; i < n-1; i++ {
		length := x[i+1] - x[i]
		rectHeight := math.Min(y[i], y[i+1])
		triangleHeight := math.Max(y[i], y[i+1]) - rectHeight

		area += rectHeight * length
		area += (triangleHeight * length) / 2
	}

	fmt.Printf("%.9f\n", area/1000)
}
