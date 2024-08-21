package main

import "fmt"

type Point struct {
	x, y float64
}

func (p Point) dot(q Point) float64 {
	return p.x*q.x + p.y*q.y
}

func (p Point) scale(f float64) Point {
	return Point{
		x: p.x * f,
		y: p.y * f,
	}
}

func (p Point) add(q Point) Point {
	return p.sub(q.scale(-1))
}

func (p Point) sub(q Point) Point {
	return Point{
		x: p.x - q.x,
		y: p.y - q.y,
	}
}

func projection(base, p Point) Point {
	return base.scale((p.dot(base)) / (base.dot(base)))
}

func main() {
	var Q int
	var p, q Point

	fmt.Scan(&p.x, &p.y, &q.x, &q.y, &Q)

	base := q.sub(p)

	for q := 0; q < Q; q++ {
		var r Point
		fmt.Scan(&r.x, &r.y)
		r = r.sub(p)
		proj := projection(base, r)
		dir := proj.sub(r)
		result := r.add(dir.scale(2)).add(p)
		fmt.Printf("%.9f %.9f\n", result.x, result.y)
	}
}
