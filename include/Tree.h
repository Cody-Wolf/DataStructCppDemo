//
// Created by cody on 23-6-28.
//

#ifndef DATASTRUCTCPPDEMO_TREE_H
#define DATASTRUCTCPPDEMO_TREE_H

#include <random>
#include "Stack.h"
#include "node/BNode.h"
#include "node/Node.h"


namespace Tree {
    std::mt19937 rnd(20010906);

    BINode *BST(const int array[], int n) {
        if (n <= 0) {
            throw std::length_error("array size should greater than 0.");
        }
        auto *root = new BINode(array[0]);
        for (int i = 1; i < n; i++) {
            auto *p = root;
            while (true) {
                if (array[i] < p->data) {
                    if (p->left) {
                        p = p->left;
                    } else {
                        p->left = BNodeFactory::create(array[i]);
                        break;
                    }
                } else {
                    if (p->right) {
                        p = p->right;
                    } else {
                        p->right = BNodeFactory::create(array[i]);
                        break;
                    }
                }
            }
        }

        return root;
    }

    BINode *randTree() {
        int size = rnd() % 10;
        int *data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = rnd() % 100;
        }

        return BST(data, size);
    }

    template<typename T>
    void preorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();

        while (!Stack::isEmpty(stack) || p) {
            while (p) {
                Stack::push(stack, p);
                std::cout << p << ' ';
                p = p->left;
            }
            p = Stack::pop(stack);
            p = p->right;
        }
    }

    template<typename T>
    void inorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();

        while (!Stack::isEmpty(stack) || p) {
            while (p) {
                Stack::push(stack, p);
                p = p->left;
            }
            p = Stack::pop(stack);
            std::cout << p << ' ';
            p = p->right;
        }
    }

    template<typename T>
    void postorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();

        while (!Stack::isEmpty(stack) || p) {
            if (p) {
                Stack::push(stack, p);
                p = p->left;
            } else {
                while (!Stack::isEmpty(stack) && Stack::top(stack)->right == p) {
                    p = Stack::pop(stack);
                    std::cout << p << ' ';
                }
                if (!Stack::isEmpty(stack)) {
                    p = Stack::top(stack)->right;
                } else {
                    p = nullptr;
                }
            }
        }
    }
}

#endif //DATASTRUCTCPPDEMO_TREE_H
