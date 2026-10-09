#include <iostream>
#include <stdexcept>
#include <vector>

class ArrayStack {
public:
    void push(int value) {
        values.push_back(value);
    }

    int pop() {
        checkNotEmpty();

        int value = values.back();
        values.pop_back();
        return value;
    }

    int peek() const {
        checkNotEmpty();
        return values.back();
    }

    bool isEmpty() const {
        return values.empty();
    }

private:
    void checkNotEmpty() const {
        if (isEmpty()) {
            throw std::underflow_error("ArrayStack is empty");
        }
    }

    std::vector<int> values;
};

void demoArrayStack() {
    std::cout << "\nArray-based stack (LIFO)\n";
    ArrayStack stack;

    try {
        stack.pop();
    } catch (const std::underflow_error& error) {
        std::cout << "  Empty removal: " << error.what() << '\n';
    }

    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << "  Pushed 1, 2, 3; top is " << stack.peek() << '\n';
    std::cout << "  Popped " << stack.pop() << '\n';

    stack.push(4);
    stack.push(5);
    std::cout << "  Pushed 4, 5; popped " << stack.pop() << " and "
              << stack.pop() << '\n';

    stack.push(6);
    std::cout << "  Pushed 6; popped " << stack.pop() << ", "
              << stack.pop() << ", " << stack.pop() << '\n';
    std::cout << "  Empty now: " << std::boolalpha << stack.isEmpty() << '\n';
}
