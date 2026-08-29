class Entry:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self, capacity=16):
        self.buckets = [None] * capacity
        self.table_size = 0

    def _hash(self, key):
        hash_value = 0

        for character in key:
            hash_value = hash_value * 31 + ord(character)

        return hash_value

    def _get_index(self, key):
        return self._hash(key) % len(self.buckets)

    def insert(self, key, value):
        index = self._get_index(key)

        current = self.buckets[index]

        while current is not None:
            if current.key == key:
                current.value = value
                return

            current = current.next

        entry = Entry(key, value)

        entry.next = self.buckets[index]
        self.buckets[index] = entry

        self.table_size += 1

    def search(self, key):
        index = self._get_index(key)

        current = self.buckets[index]

        while current is not None:
            if current.key == key:
                return current.value

            current = current.next

        return None

    def update(self, key, value):
        index = self._get_index(key)

        current = self.buckets[index]

        while current is not None:
            if current.key == key:
                current.value = value
                return True

            current = current.next

        return False

    def delete(self, key):
        index = self._get_index(key)

        current = self.buckets[index]
        previous = None

        while current is not None:
            if current.key == key:
                if previous is None:
                    self.buckets[index] = current.next
                else:
                    previous.next = current.next

                self.table_size -= 1
                return True

            previous = current
            current = current.next

        return False

    def contains(self, key):
        return self.search(key) is not None

    def size(self):
        return self.table_size


table = HashTable()

table.insert("name", "Zia")
table.insert("language", "Python")
table.insert("level", "beginner")

print("Search:", table.search("language"))

table.update("level", "intermediate")

print("Contains name:", table.contains("name"))

table.delete("language")

print("Size:", table.size())