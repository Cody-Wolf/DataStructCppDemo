//
// Created by cody on 23-6-28.
//

#ifndef DATASTRUCTCPPDEMO_BNODE_H
#define DATASTRUCTCPPDEMO_BNODE_H

#include <iostream>

template<typename T>
class BNode {
public:
    T data;
    BNode *left;
    BNode *right;

    explicit BNode(T data) {
        this->data = data;
    }

    static BNode<T> *of(T data) {
        return new BNode<T>(data);
    }

    friend std::ostream &operator<<(std::ostream &out, const BNode &node) {
        return out << node.data;
    }

    friend std::ostream &operator<<(std::ostream &out, const BNode *node) {
        return out << node->data;
    }
};

class BNodeFactory {
public:
    template<typename T>
    static BNode<T> *create(T data) {
        return new BNode<T>(data);
    }
};

typedef BNode<int> BINode;


#endif //DATASTRUCTCPPDEMO_BNODE_H
