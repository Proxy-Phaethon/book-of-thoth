class Queue:
    def __init__(self):
        self.data = []
        self.front_index = 0

    def enqueue(self, value):
        self.data.append(value)

    def dequeue(self):
        if self.is_empty():
            return None

        value = self.data[self.front_index]
        self.front_index += 1

        # Reset the queue when all elements have been removed.
        if self.front_index == len(self.data):
            self.data = []
            self.front_index = 0

        return value

    def front(self):
        if self.is_empty():
            return None

        return self.data[self.front_index]

    def is_empty(self):
        return self.front_index == len(self.data)

    def size(self):
        return len(self.data) - self.front_index


queue = Queue()

queue.enqueue(10)
queue.enqueue(20)
queue.enqueue(30)

print("Front:", queue.front())
print("Dequeue:", queue.dequeue())

queue.enqueue(40)

print("Size:", queue.size())