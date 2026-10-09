#include <iostream>
#include <stdexcept>

class LinkedDeque {
private:
    struct Node {
        int value;
        Node* previous;
        Node* next;

        explicit Node(int value)
            : value(value), previous(nullptr), next(nullptr) {}
    };

public:
    LinkedDeque() : frontNode(nullptr), backNode(nullptr) {}
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;

    ~LinkedDeque() {
        while (frontNode != nullptr) {
            Node* nextNode = frontNode->next;
            delete frontNode;
            frontNode = nextNode;
        }
    }

    void addFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = frontNode;

        if (isEmpty()) {
            backNode = newNode;
        } else {
            frontNode->previous = newNode;
        }

        frontNode = newNode;
    }

    void addBack(int value) {
        Node* newNode = new Node(value);
        newNode->previous = backNode;

        if (isEmpty()) {
            frontNode = newNode;
        } else {
            backNode->next = newNode;
        }

        backNode = newNode;
    }

    int removeFront() {
        checkNotEmpty();

        Node* removedNode = frontNode;
        int value = removedNode->value;
        frontNode = removedNode->next;
        delete removedNode;

        if (frontNode == nullptr) {
            backNode = nullptr;
        } else {
            frontNode->previous = nullptr;
        }

        return value;
    }

    int removeBack() {
        checkNotEmpty();

        Node* removedNode = backNode;
        int value = removedNode->value;
        backNode = removedNode->previous;
        delete removedNode;

        if (backNode == nullptr) {
            frontNode = nullptr;
        } else {
            backNode->next = nullptr;
        }

        return value;
    }

    int peekFront() const {
        checkNotEmpty();
        return frontNode->value;
    }

    int peekBack() const {
        checkNotEmpty();
        return backNode->value;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

private:
    void checkNotEmpty() const {
        if (isEmpty()) {
            throw std::underflow_error("LinkedDeque is empty");
        }
    }

    Node* frontNode;
    Node* backNode;
};

void demoLinkedDeque() {
    std::cout << "\nLinked-list deque\n";
    LinkedDeque deque;

    try {
        deque.removeBack();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    deque.addBack(10);
    deque.addFront(20);
    deque.addBack(30);
    std::cout << "  Added 10 at back, 20 at front, 30 at back; ends are "
              << deque.peekFront() << " and " << deque.peekBack() << '\n';
    std::cout << "  Removed from front: " << deque.removeFront() << '\n';

    deque.addFront(40);
    deque.addBack(50);
    std::cout << "  Added 40 at front and 50 at back; removed from back: "
              << deque.removeBack() << '\n';
    std::cout << "  Removed from front: " << deque.removeFront() << '\n';

    deque.addBack(60);
    std::cout << "  Added 60 at back; removed " << deque.removeBack() << ", "
              << deque.removeFront() << ", " << deque.removeFront() << '\n';
    std::cout << "  Empty now: " << deque.isEmpty() << '\n';
}
