class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        self.root = self._insert(self.root, value)

    def _insert(self, node, value):
        if node is None:
            return Node(value)

        if value < node.value:
            node.left = self._insert(node.left, value)
        elif value > node.value:
            node.right = self._insert(node.right, value)

        return node

    def search(self, value):
        return self._search(self.root, value)

    def _search(self, node, value):
        if node is None:
            return False

        if node.value == value:
            return True

        if value < node.value:
            return self._search(node.left, value)

        return self._search(node.right, value)

    def delete(self, value):
        self.root = self._delete(self.root, value)

    def _delete(self, node, value):
        if node is None:
            return None

        if value < node.value:
            node.left = self._delete(node.left, value)

        elif value > node.value:
            node.right = self._delete(node.right, value)

        else:
            # No children.
            if node.left is None and node.right is None:
                return None

            # Only right child.
            if node.left is None:
                return node.right

            # Only left child.
            if node.right is None:
                return node.left

            # Two children.
            successor = self._find_min(node.right)

            node.value = successor.value
            node.right = self._delete(
                node.right,
                successor.value
            )

        return node

    def _find_min(self, node):
        current = node

        while current.left is not None:
            current = current.left

        return current

    def inorder(self):
        result = []
        self._inorder(self.root, result)
        print(*result)

    def _inorder(self, node, result):
        if node is None:
            return

        self._inorder(node.left, result)
        result.append(node.value)
        self._inorder(node.right, result)

    def preorder(self):
        result = []
        self._preorder(self.root, result)
        print(*result)

    def _preorder(self, node, result):
        if node is None:
            return

        result.append(node.value)
        self._preorder(node.left, result)
        self._preorder(node.right, result)

    def postorder(self):
        result = []
        self._postorder(self.root, result)
        print(*result)

    def _postorder(self, node, result):
        if node is None:
            return

        self._postorder(node.left, result)
        self._postorder(node.right, result)
        result.append(node.value)


tree = BinarySearchTree()

tree.insert(50)
tree.insert(30)
tree.insert(70)
tree.insert(20)
tree.insert(40)
tree.insert(60)
tree.insert(80)

print("In-order:", end=" ")
tree.inorder()

print("Pre-order:", end=" ")
tree.preorder()

print("Post-order:", end=" ")
tree.postorder()

print(
    "Search 40:",
    "found" if tree.search(40) else "not found"
)

tree.delete(30)

print("After deleting 30:", end=" ")
tree.inorder()