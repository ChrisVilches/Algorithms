package main

import (
	"fmt"
	"math"
)

type Target interface {
	inside(x, y int) bool
}

type Rectangle struct {
	x1, y1, x2, y2 int
}

func (r Rectangle) inside(x, y int) bool {
	return r.x1 <= x && x <= r.x2 && r.y1 <= y && y <= r.y2
}

type Circle struct {
	x, y, r int
}

func (c Circle) inside(x, y int) bool {
	return math.Hypot(float64(x-c.x), float64(y-c.y)) <= float64(c.r)
}

func main() {
	var m, n int
	fmt.Scan(&m)

	targets := []Target{}

	for i := 0; i < m; i++ {
		var s string
		fmt.Scanf("%v", &s)
		if s == "rectangle" {
			var r Rectangle
			fmt.Scanf("%d %d %d %d", &r.x1, &r.y1, &r.x2, &r.y2)
			targets = append(targets, r)
		} else {
			var c Circle
			fmt.Scanf("%d %d %d", &c.x, &c.y, &c.r)
			targets = append(targets, c)
		}
	}

	fmt.Scan(&n)

	for i := 0; i < n; i++ {
		total := 0
		var x, y int
		fmt.Scanf("%d %d", &x, &y)

		for _, t := range targets {
			if t.inside(x, y) {
				total++
			}
		}

		fmt.Println(total)
	}
}
