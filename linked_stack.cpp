#include <iostream>
#include <stdexcept>

class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;

        explicit Node(int value) : value(value), next(nullptr) {}
    };

public:
    LinkedStack() : topNode(nullptr) {}
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    ~LinkedStack() {
        while (topNode != nullptr) {
            Node* nextNode = topNode->next;
            delete topNode;
            topNode = nextNode;
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        checkNotEmpty();

        Node* removedNode = topNode;
        int value = removedNode->value;
        topNode = removedNode->next;
        delete removedNode;
        return value;
    }

    int peek() const {
        checkNotEmpty();
        return topNode->value;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

private:
    void checkNotEmpty() const {
        if (isEmpty()) {
            throw std::underflow_error("LinkedStack is empty");
        }
    }

    Node* topNode;
};

void demoLinkedStack() {
    std::cout << "\nLinked-list stack (LIFO)\n";
    LinkedStack stack;

    try {
        stack.pop();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "  Pushed 10, 20, 30; top is " << stack.peek() << '\n';
    std::cout << "  Popped " << stack.pop() << '\n';

    stack.push(40);
    stack.push(50);
    std::cout << "  Pushed 40, 50; popped " << stack.pop() << " and "
              << stack.pop() << '\n';

    stack.push(60);
    std::cout << "  Pushed 60; popped " << stack.pop() << ", "
              << stack.pop() << ", " << stack.pop() << '\n';
    std::cout << "  Empty now: " << stack.isEmpty() << '\n';
}
