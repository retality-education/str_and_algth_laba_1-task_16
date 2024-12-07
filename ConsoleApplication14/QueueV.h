#pragma once
#include <fstream>
#include <iostream>

// ��� ������ ��� ������������� � �������
using TInfo = int;

// ���� ��� ������ (���� ����� ����� ���������� ���������)
struct NODE {
    TInfo info;
    NODE* next;
    NODE(TInfo info, NODE* ptr = nullptr) : info(info), next(ptr) {}
};

const size_t MaxCount = 100;

struct QueueV {
private:
    TInfo elements[MaxCount];
    int tail;
    int head;
    void left_shift() {
        for (int i{}; i <= tail; ++i)
            elements[i] = elements[i + head];
    }
public:
    QueueV() : tail(-1), head(0) {}

    bool empty();

    bool full();

    size_t size();

    void push(TInfo elem);

    void pop();

    TInfo front();

    void view();

    void clear();

    void fill_q_from_file(const std::string& filename);
};