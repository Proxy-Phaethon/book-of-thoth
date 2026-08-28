class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def append(self, value):
        new_node = Node(value)

        if self.head is None:
            self.head = new_node
            return

        current = self.head

        while current.next is not None:
            current = current.next

        current.next = new_node

    def prepend(self, value):
        new_node = Node(value)

        new_node.next = self.head
        self.head = new_node

    def insert(self, value, index):
        if index < 0:
            return

        if index == 0:
            self.prepend(value)
            return

        current = self.head

        for _ in range(index - 1):
            if current is None:
                return

            current = current.next

        if current is None:
            return

        new_node = Node(value)

        new_node.next = current.next
        current.next = new_node

    def delete(self, value):
        if self.head is None:
            return

        if self.head.value == value:
            self.head = self.head.next
            return

        current = self.head

        while current.next is not None:
            if current.next.value == value:
                current.next = current.next.next
                return

            current = current.next

    def search(self, value):
        current = self.head
        index = 0

        while current is not None:
            if current.value == value:
                return index

            current = current.next
            index += 1

        return -1

    def print_list(self):
        current = self.head

        while current is not None:
            print(current.value, end="")

            if current.next is not None:
                print(" ", end="")

            current = current.next

        print()


list = LinkedList()

list.append(10)
list.append(20)
list.append(30)

list.prepend(5)

list.insert(15, 2)

list.delete(20)

print("List:", end=" ")
list.print_list()

print("Search result:", list.search(30))