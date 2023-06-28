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
        auto *root = new BINode(int(rnd()) % 100);
        auto *stack = Stack::emptyStack<BINode *>();

        Stack::push(stack, root);

        while (!Stack::isEmpty(stack)) {
            BINode *top = Stack::pop(stack);
            if (rnd() % 10 < 5) {
                top->left = new BINode(int(rnd()) % top->data);
                Stack::push(stack, top->left);
            }
            if (rnd() % 10 < 5) {
                top->right = new BINode(top->data);
                Stack::push(stack, top->right);
            }
        }

        return root;
    }

    template<typename T>
    void preorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();
        Stack::push(stack, p);
        while (!Stack::isEmpty(stack)) {
            auto *top = Stack::pop(stack);
            std::cout << top->data << " ";
            if (top->right) {
                Stack::push(stack, top->right);
            }
            if (top->left) {
                Stack::push(stack, top->left);
            }
        }
    }

    template<typename T>
    void inorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();
        auto *wait = Stack::emptyStack<BNode<T> *>();
        Stack::push(stack, p);

        while (!Stack::isEmpty(stack) || !Stack::isEmpty(wait)) {
            if (!Stack::isEmpty(stack)) {
                auto *top = Stack::pop(stack);
                Stack::push(wait, top);
                if (top->left) {
                    Stack::push(stack, top->left);
                }
            } else {
                auto *top = Stack::pop(wait);
                std::cout << top->data << " ";
                if (top->right) {
                    Stack::push(stack, top->right);
                }
            }
        }
    }

    template<typename T>
    void postorder(BNode<T> *p) {
        auto *stack = Stack::emptyStack<BNode<T> *>();
        auto *wait = Stack::emptyStack<BNode<T> *>();
        Stack::push(stack, p);

        while (!Stack::isEmpty(stack)) {
            if (Stack::top(stack) == Stack::top(wait)) {
                    std::cout << Stack::pop(stack) << ' ';
                    Stack::pop(wait);
            } else {
                auto *top = Stack::top(stack);
                Stack::push(wait, top);

                if (top->right) {
                    Stack::push(stack, top->right);
                }

                if (top->left) {
                    Stack::push(stack, top->left);
                }
            }
        }
    }
}

#endif //DATASTRUCTCPPDEMO_TREE_H
