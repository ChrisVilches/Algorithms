package main

import (
	"fmt"
	"math"
)

type Sphere struct {
	r, x, y, z float64
}

func (s Sphere) cap(h float64) float64 {
	return (math.Pi * h * h / 3) * (3*s.r - h)
}

func (s Sphere) volume() float64 {
	return 4 * math.Pi * math.Pow(s.r, 3) / 3
}

func (s Sphere) partialVolume(z0 float64) float64 {
	if z0 <= s.z {
		minz := s.z - s.r
		z0 = math.Max(z0, minz)
		return s.cap(z0 - minz)
	} else {
		maxz := s.z + s.r
		z0 = math.Min(z0, maxz)
		return s.volume() - s.cap(maxz-z0)
	}
}

var (
	holes [10001]Sphere
	N, S  int
)

func cheeseVolume(z float64) float64 {
	total := 1e15 * z / 100000

	for i := 0; i < N; i++ {
		total -= holes[i].partialVolume(z)
	}

	return total
}

func main() {
	fmt.Scan(&N, &S)

	for i := 0; i < N; i++ {
		fmt.Scan(&holes[i].r, &holes[i].x, &holes[i].y, &holes[i].z)
	}

	var fullVolume float64 = 1e15

	for i := 0; i < N; i++ {
		fullVolume -= holes[i].volume()
	}

	var oneSlice float64 = fullVolume / float64(S)

	var prevPartition float64 = 0

	for i := 1; i <= S; i++ {
		var left float64 = 0
		var right float64 = 100000

		required := oneSlice * float64(i)

		for right-left > 1e-7 {
			var mid float64 = (right + left) / 2
			if cheeseVolume(mid) < required {
				left = mid
			} else {
				right = mid
			}
		}

		fmt.Printf("%.9f\n", (left-prevPartition)/1000)
		prevPartition = left
	}
}
