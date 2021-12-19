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
    void flood(int data, unsigned start = 0, int end = -1);
    void print();

    //operators
    const size_t size_of();
    Node* operator()(unsigned index); //operator[] coincided with the built-in operator[] for pointers
    operator Node** (); //casting operator
    //friend std::ostream& operator<<(std::ostream os, const LL& ll);

private:
    Node* head;
    int _size;
    bool diverse; //future plans
    
    Node** arr = nullptr; //pay no attention, casting purposes only.
};

/*
* TODO:
* TEMPLATE-IFY LINKED LIST CLASS
* ADD OPTION FOR DIVERSIFICATION: NODES OF DIFFERENT TYPES IN SAME LINKED LIST
* FOLLOWING UP, ADD OPTION FOR DE-DIVERSIFICATION: CONVERT ALL NODES TO SAME TYPE (IF POSSIBLE)
* 
* flood function will not work with diversified linked lists.
*/