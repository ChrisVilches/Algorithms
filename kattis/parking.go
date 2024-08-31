package main

import (
	"fmt"
	"sort"
)

type Pair struct{ time, delta int }

func main() {
	var a, b, c int
	fmt.Scanf("%d %d %d", &a, &b, &c)

	events := []Pair{}

	for i := 0; i < 3; i++ {
		var a, b int
		fmt.Scanf("%d %d", &a, &b)
		events = append(events, Pair{time: a, delta: 1})
		events = append(events, Pair{time: b, delta: -1})
	}

	sort.Slice(events, func(i, j int) bool {
		return events[i].time < events[j].time
	})

	cost := 0
	curr := 0
	prev_time := 0

	costs := []int{0, a, b, c}

	for _, ev := range events {
		cost += costs[curr] * curr * (ev.time - prev_time)

		prev_time = ev.time

		curr += ev.delta
	}

	fmt.Println(cost)
}
