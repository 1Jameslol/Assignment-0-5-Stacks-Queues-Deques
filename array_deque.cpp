#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class ArrayDeque {
public:
    ArrayDeque() : values(4), frontIndex(0), itemCount(0) {}

    void addFront(int value) {
        makeSpaceIfFull();
        frontIndex = (frontIndex + values.size() - 1) % values.size();
        values[frontIndex] = value;
        itemCount++;
    }

    void addBack(int value) {
        makeSpaceIfFull();
        std::size_t insertIndex = (frontIndex + itemCount) % values.size();
        values[insertIndex] = value;
        itemCount++;
    }

    int removeFront() {
        checkNotEmpty();

        int value = values[frontIndex];
        frontIndex = (frontIndex + 1) % values.size();
        itemCount--;
        return value;
    }

    int removeBack() {
        checkNotEmpty();

        std::size_t backIndex = (frontIndex + itemCount - 1) % values.size();
        int value = values[backIndex];
        itemCount--;
        return value;
    }

    int peekFront() const {
        checkNotEmpty();
        return values[frontIndex];
    }

    int peekBack() const {
        checkNotEmpty();
        std::size_t backIndex = (frontIndex + itemCount - 1) % values.size();
        return values[backIndex];
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

private:
    void makeSpaceIfFull() {
        if (itemCount < values.size()) {
            return;
        }

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
            throw std::underflow_error("ArrayDeque is empty");
        }
    }

    std::vector<int> values;
    std::size_t frontIndex;
    std::size_t itemCount;
};

void demoArrayDeque() {
    std::cout << "\nArray-based deque\n";
    ArrayDeque deque;

    try {
        deque.removeFront();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    deque.addBack(1);
    deque.addFront(2);
    deque.addBack(3);
    std::cout << "  Added 1 at back, 2 at front, 3 at back; ends are "
              << deque.peekFront() << " and " << deque.peekBack() << '\n';
    std::cout << "  Removed from front: " << deque.removeFront() << '\n';

    deque.addFront(4);
    deque.addBack(5);
    std::cout << "  Added 4 at front and 5 at back; removed from back: "
              << deque.removeBack() << '\n';
    std::cout << "  Removed from front: " << deque.removeFront() << '\n';

    deque.addBack(6);
    std::cout << "  Added 6 at back; removed " << deque.removeBack() << ", "
              << deque.removeFront() << ", " << deque.removeFront() << '\n';
    std::cout << "  Empty now: " << deque.isEmpty() << '\n';
}
