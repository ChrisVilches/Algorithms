package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	bitTree [500007]int
	N       int
)

func query(i int) int {
	i++
	sum := 0
	for ; i > 0; i -= i & -i {
		sum += bitTree[i]
	}
	return sum
}

func update(i int, v int) {
	i++
	for ; i <= N; i += i & -i {
		bitTree[i] += v
	}
}

func main() {
	in := bufio.NewReader(os.Stdin)

	fmt.Fscan(in, &N)

	for i := 0; i < N; i++ {
		update(i, 1)
	}

	for i := 0; i < N; i++ {
		var x int
		fmt.Fscan(in, &x)
		x--

		index := query(x)

		if i > 0 {
			fmt.Print(" ")
		}

		fmt.Print(index)

		update(x, -1)
	}

	fmt.Println()
}
