//
// Created by cody on 23-6-28.
//

#ifndef DATASTRUCTCPPDEMO_NODE_H
#define DATASTRUCTCPPDEMO_NODE_H

#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node *next;

    Node() = default;

    explicit Node(T data) : Node(data, nullptr) {}

    Node(T data, Node *next) {
        this->data = data;
        this->next = next;
    }

    ~Node() {
        delete next;
    }

    explicit Node(Node *p) {
        this->data = p->data;
        this->next = p->next;
    }

    friend std::ostream &operator<<(std::ostream &out, const Node &node) {
        Node *p = node.next;
        out << "[";
        while (p) {
            out << p->data;
            if (p->next) {
                out << ", ";
            }
            p = p->next;
        }
        return out << "]";
    }

    friend std::ostream &operator<<(std::ostream &out, const Node *node) {
        return out << *node;
    }
};

class NodeFactory {
public:
    template<typename T>
    static Node<T> *create(T data) {
        return new Node<T>(data);
    }
};

typedef Node<int> INode;

#endif //DATASTRUCTCPPDEMO_NODE_H
