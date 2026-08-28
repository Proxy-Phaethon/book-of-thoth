class Stack:
    def __init__(self):
        self.data = []

    def push(self, value):
        self.data.append(value)

    def pop(self):
        if self.is_empty():
            return None

        return self.data.pop()

    def peek(self):
        if self.is_empty():
            return None

        return self.data[-1]

    def is_empty(self):
        return len(self.data) == 0

    def size(self):
        return len(self.data)


stack = Stack()

stack.push(10)
stack.push(20)
stack.push(30)

print("Peek:", stack.peek())
print("Pop:", stack.pop())

stack.push(40)

print("Size:", stack.size())