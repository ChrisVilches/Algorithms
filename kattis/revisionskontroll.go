package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var n, x int
	in := bufio.NewReader(os.Stdin)
	fmt.Fscan(in, &n)
	visited := make(map[int]int)

	for i := 0; i < n; i++ {
		fmt.Fscan(in, &x)
		fmt.Print(visited[x]^1, " ")
		visited[x] = 1
	}

	fmt.Println()
}
