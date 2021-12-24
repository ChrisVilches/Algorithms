class TreeNode:
    value = None
    left = None
    right = None

    def __init__(self, v):
        self.value = v

    def hash(self, factor):
        total = 0

        if self.left:
            total += 0x4234 * factor * self.left.hash(factor * 3)
        else:
            total += 0x434347 * factor

        if self.right:
            total += 0x4114 * factor * self.right.hash(factor * 2)
        else:
            total += 0x1911913 * factor

        return total

    def insert(self, v):
        if v <= self.value:
            if self.left:
                self.left.insert(v)
            else:
                self.left = TreeNode(v)
        else:
            if self.right:
                self.right.insert(v)
            else:
                self.right = TreeNode(v)


n, k = map(int, input().split())

tree_shapes = set()

for _ in range(n):
    values = list(map(int, input().split()))

    root = TreeNode(values[0])

    for i in range(1, k):
        root.insert(values[i])

    tree_shapes.add(root.hash(1))

print(len(tree_shapes))
