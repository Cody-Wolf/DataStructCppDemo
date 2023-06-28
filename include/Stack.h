//
// Created by cody on 23-6-28.
//

#ifndef DATASTRUCTCPPDEMO_STACK_H
#define DATASTRUCTCPPDEMO_STACK_H

#include "node/Node.h"

namespace Stack {

    template<typename T>
    Node<T> *emptyStack() {
        return new Node<T>();
    }

    template<typename T>
    void push(Node<T> *top, T data) {
        Node<T>* x = NodeFactory::create(data);
        x->next = top->next;
        top->next = x;
    }

    template<typename T>
    T pop(Node<T> *top) {
        Node<T> *result = top->next;
        top->next = top->next->next;
        result->next = nullptr;
        return result->data;
    }

    template<typename T>
    T top(Node<T> *top) {
        return top->next ? top->next->data : nullptr;
    }

    template<typename T>
    bool isEmpty(Node<T> *top) {
        return !top->next;
    }
};


#endif //DATASTRUCTCPPDEMO_STACK_H
