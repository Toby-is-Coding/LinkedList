#pragma once
#include <iostream>
struct Node {
    int data;
    Node* ptr;
    void cut(Node* qJumper) {
        qJumper->ptr = ptr;
        ptr = qJumper;
    }
};

class LL {
public:
    LL();
    LL(int size);
    LL(const LL&);
    ~LL();

    //funcs
    const int size() const;
    void erase(unsigned index, unsigned plus = 0);
    void insert(Node** nodes, unsigned index = 0, unsigned amount = 1);
    void flood(int data, int start = 0, int end = -1);
    void print();

    //operators
    const size_t size_of();
    Node* operator[](unsigned index);
    operator Node** (); //casting operator
    //friend std::ostream& operator<<(std::ostream os, const LL& ll);

private:
    Node* head;
    int _size;
    
    Node** arr = nullptr; //pay no attention, casting purposes only.
};