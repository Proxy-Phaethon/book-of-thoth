class MaxHeap:
    def __init__(self):
        self.data = []

    def _swap(self, first, second):
        self.data[first], self.data[second] = (
            self.data[second],
            self.data[first]
        )

    def _sift_up(self, index):
        while index > 0:
            parent = (index - 1) // 2

            if self.data[parent] >= self.data[index]:
                break

            self._swap(parent, index)

            index = parent

    def _sift_down(self, index):
        while True:
            left = 2 * index + 1
            right = 2 * index + 2
            largest = index

            if (
                left < len(self.data)
                and self.data[left] > self.data[largest]
            ):
                largest = left

            if (
                right < len(self.data)
                and self.data[right] > self.data[largest]
            ):
                largest = right

            if largest == index:
                break

            self._swap(index, largest)

            index = largest

    def insert(self, value):
        self.data.append(value)

        self._sift_up(len(self.data) - 1)

    def extract_max(self):
        if self.is_empty():
            return None

        maximum = self.data[0]

        self.data[0] = self.data[-1]
        self.data.pop()

        if not self.is_empty():
            self._sift_down(0)

        return maximum

    def peek_max(self):
        if self.is_empty():
            return None

        return self.data[0]

    def heapify(self):
        for index in range(len(self.data) // 2 - 1, -1, -1):
            self._sift_down(index)

    def is_empty(self):
        return len(self.data) == 0

    def size(self):
        return len(self.data)


heap = MaxHeap()

heap.insert(40)
heap.insert(20)
heap.insert(70)
heap.insert(10)
heap.insert(90)
heap.insert(50)

print("Peek Max:", heap.peek_max())
print("Extract Max:", heap.extract_max())
print("Size:", heap.size())