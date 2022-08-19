package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func listSize(head *ListNode) int {
	n := 0

	for head != nil {
		n++
		head = head.Next
	}

	return n
}

func removeAt(head *ListNode, removeIdx int) {
	for i := 0; head != nil; i++ {
		if i+1 == removeIdx {
			head.Next = head.Next.Next
		}

		head = head.Next
	}
}

func deleteMiddle(head *ListNode) *ListNode {
	n := listSize(head)

	if n == 1 {
		return nil
	}

	mid := n / 2

	removeAt(head, mid)
	return head
}
