package main

import (
	"fmt"
	"reflect"
)

var allShapes = [][][]int{
	{{}, {0, 0, 0}},
	{{0}},
	{{0, 1}, {-1}},
	{{-1, -1}, {1}},
	{{0, 0}, {-1}, {1}, {-1, 0}},
	{{0, 0}, {-2}, {0}, {1, 1}},
	{{0, 0}, {2}, {0}, {0, -1}},
}

func main() {
	var c, p int
	fmt.Scan(&c, &p)

	cols := make([]int, c)
	for i := range cols {
		fmt.Scan(&cols[i])
	}

	ans := 0

	for _, shape := range allShapes[p-1] {
		for i := range cols {
			curr := []int{}

			for j := i + 1; j < c && len(curr) < len(shape); j++ {
				curr = append(curr, cols[j]-cols[i])
			}

			if reflect.DeepEqual(curr, shape) {
				ans++
			}
		}
	}

	fmt.Println(ans)
}
