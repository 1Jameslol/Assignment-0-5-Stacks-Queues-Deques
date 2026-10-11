#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class ArrayQueue {
public:
    ArrayQueue() : values(4), frontIndex(0), itemCount(0) {}


    //These functions do the same kind of logic as the deque but a different calculation to find the new indices
    void enqueue(int value) {
        if (itemCount == values.size()) {
            grow();
        }

        std::size_t insertIndex = (frontIndex + itemCount) % values.size();
        values[insertIndex] = value;
        itemCount++;
    }

    int dequeue() {
        checkNotEmpty();

        int value = values[frontIndex];
        frontIndex = (frontIndex + 1) % values.size();
        itemCount--;
        return value;
    }

    int peek() const {
        checkNotEmpty();
        return values[frontIndex];
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

private:

    //The grow function doubles the arrays size and uses iteration to copy the items
    void grow() {
        std::vector<int> largerValues(values.size() * 2);

        for (std::size_t i = 0; i < itemCount; i++) {
            std::size_t oldIndex = (frontIndex + i) % values.size();
            largerValues[i] = values[oldIndex];
        }

        values = largerValues;
        frontIndex = 0;
    }

    void checkNotEmpty() const {
        if (isEmpty()) {
            throw std::underflow_error("ArrayQueue is empty");
        }
    }

    std::vector<int> values;
    std::size_t frontIndex;
    std::size_t itemCount;
};

//Array queue tests
void demoArrayQueue() {
    std::cout << "\nArray-based queue (FIFO)\n";
    ArrayQueue queue;

    try {
        queue.dequeue();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "  Enqueued 1, 2, 3; front is " << queue.peek() << '\n';
    std::cout << "  Removed " << queue.dequeue() << '\n';

    queue.enqueue(4);
    queue.enqueue(5);
    std::cout << "  Enqueued 4, 5; removed " << queue.dequeue() << " and "
              << queue.dequeue() << '\n';

    queue.enqueue(6);
    std::cout << "  Enqueued 6; removed " << queue.dequeue() << ", "
              << queue.dequeue() << ", " << queue.dequeue() << '\n';
    std::cout << "  Empty now: " << queue.isEmpty() << '\n';
}
