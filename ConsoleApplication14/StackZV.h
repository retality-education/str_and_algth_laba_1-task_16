#pragma once
template <typename T>
class StackZV {
    struct NODE // Узел списка, т.е 1 элемент. Хранит адрес на элемент справа и само значение
    {
        T info;
        NODE* next; // указатель на точно такой же узел

        NODE(T info, NODE* ptr = nullptr) : info(info), next(ptr) {};
        ~NODE() { next = nullptr;/*0*/ }

    };
    using ptrNODE = NODE*;

private:
    size_t sizeOfStack;
    NODE* currentTop;
    const size_t MaxCount = 100;
    ptrNODE copy(const ptrNODE ptr)
    {
        ptrNODE result = nullptr;
        if (ptr)
            result = new NODE(ptr->info, copy(ptr->next));
        return result;
    }
public:
    StackZV() {
        sizeOfStack = 0;
        currentTop = NULL;
    }

    ~StackZV() {
        while (size())
            pop();
    }
    void push(const T element) {
        if (full()) throw std::runtime_error("Stack overflow!");
        NODE* node = new NODE(element, currentTop);
        sizeOfStack++;
        currentTop = node;
    }

    void pop() {
        if (empty()) throw std::runtime_error("Stack is empty!");
        sizeOfStack--;
        NODE* node = currentTop;
        currentTop = currentTop->next;
        delete node;
    }
    bool full() {
        return sizeOfStack == MaxCount - 1;
    }
    T top() {
        if (empty()) throw std::runtime_error("Stack is empty!");
        return currentTop->info;
    }

    unsigned int size() {
        return sizeOfStack;
    }
    bool empty() {
        return sizeOfStack == 0;
    }
    ptrNODE current_top() {
        if (empty()) throw std::runtime_error("Stack is empty!");
        return currentTop;
    }

    void copyq(StackZV& stack) {
        if (stack.empty()) throw std::runtime_error("Stack is empty!");
        currentTop = copy(stack.current_top());
        sizeOfStack = stack.size();
    }
};