// TODO: Fix this shit

func mergeKLists(lists []*ListNode) *ListNode {
	all := []int{}

	for _, head := range lists {
		curr := head
		for curr != nil {
			all = append(all, curr.Val)
			curr = curr.Next
		}
	}

	sort.Ints(all)

	if len(all) == 0 {
		return nil
	}

	result := ListNode{
		Val:  all[0],
		Next: nil,
	}
	curr := &result

	for i := 1; i < len(all); i++ {
		curr.Next = &ListNode{
			Val:  all[i],
			Next: nil,
		}
		curr = curr.Next
	}

	return &result
}
