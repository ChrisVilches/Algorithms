package main

type NumArray struct {
	psum []int
}

func Constructor(nums []int) NumArray {
	var na NumArray

	na.psum = append(na.psum, 0)

	for _, x := range nums {
		prev := na.psum[len(na.psum)-1]
		na.psum = append(na.psum, prev+x)
	}

	return na
}

func (this *NumArray) SumRange(left int, right int) int {
	return this.psum[right+1] - this.psum[left]
}
