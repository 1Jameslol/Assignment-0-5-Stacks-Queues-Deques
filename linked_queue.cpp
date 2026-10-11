#include <iostream>
#include <stdexcept>

class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;

        explicit Node(int value) : value(value), next(nullptr) {}
    };

public:
    LinkedQueue() : frontNode(nullptr), backNode(nullptr) {}
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;
    //Destructor
    ~LinkedQueue() {
        while (frontNode != nullptr) {
            Node* nextNode = frontNode->next;
            delete frontNode;
            frontNode = nextNode;
        }
    }
   //Uses the node logic to add or remove nodes
    void enqueue(int value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            frontNode = newNode;
            backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    int dequeue() {
        checkNotEmpty();

        Node* removedNode = frontNode;
        int value = removedNode->value;
        frontNode = removedNode->next;
        delete removedNode;

        if (frontNode == nullptr) {
            backNode = nullptr;
        }

        return value;
    }

    int peek() const {
        checkNotEmpty();
        return frontNode->value;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

private:
    void checkNotEmpty() const {
        if (isEmpty()) {
            throw std::underflow_error("LinkedQueue is empty");
        }
    }

    Node* frontNode;
    Node* backNode;
};

//Tests the LinkedQueue
void demoLinkedQueue() {
    std::cout << "\nLinked-list queue (FIFO)\n";
    LinkedQueue queue;

    try {
        queue.dequeue();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "  Enqueued 10, 20, 30; front is " << queue.peek() << '\n';
    std::cout << "  Removed " << queue.dequeue() << '\n';

    queue.enqueue(40);
    queue.enqueue(50);
    std::cout << "  Enqueued 40, 50; removed " << queue.dequeue() << " and "
              << queue.dequeue() << '\n';

    queue.enqueue(60);
    std::cout << "  Enqueued 60; removed " << queue.dequeue() << ", "
              << queue.dequeue() << ", " << queue.dequeue() << '\n';
    std::cout << "  Empty now: " << queue.isEmpty() << '\n';
}
