func reverseList(head *ListNode) *ListNode {
	curr := head
	var prev_node *ListNode = nil

	for curr != nil {
		next_node := curr.Next
		curr.Next = prev_node
		prev_node = curr
		curr = next_node
	}

	return prev_node
}
