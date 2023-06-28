//
// Created by cody on 23-6-28.
//

#ifndef DATASTRUCTCPPDEMO_LIST_H
#define DATASTRUCTCPPDEMO_LIST_H

#include "node/Node.h"

namespace List {
    template<typename T>
    Node<T> *emptyList() {
        return new Node<T>();
    }

    template<typename T>
    void insertBack(Node<T> *head, Node<T> *x) {
        if (head->next) {
            if (x->next) {
                throw std::invalid_argument("next pointer of inserting Node is not nullptr. ");
            }
            x->next = head->next;
        }
        head->next = x;
    }

    template<typename T>
    Node<T> *copyOf(Node<T> *p) {
        auto *head = new Node<T>(p);
        Node<T> *q = head;
        while (p->next) {
            q->next = new Node<T>(p->next);
            q = q->next;
            p = p->next;
        }

        return head;
    }

    template<typename T>
    Node<T> *asList(T array[], int n) {
        Node<T> *list = emptyList<T>();
        for (int i = n - 1; i >= 0; i--) {
            insertBack(list, NodeFactory::create(array[i]));
        }

        return list;
    }

    template<typename T>
    Node<T> *asList2(T array[], int n) {
        Node<T> *list = emptyList<T>();
        Node<T> *p = list;
        for (int i = 0; i < n; i++) {
            insertBack(p, NodeFactory::create(array[i]));
            p = p->next;
        }

        return list;
    }

    template<typename T>
    Node<T> *getKth(Node<T> *p, int k) {
        while (k && p->next) {
            k--;
            p = p->next;
        }
        if (k) {
            return nullptr;
        }

        return p;
    }

    template<typename T>
    Node<T> *getLastKth(Node<T> *p, int k) {
        Node<T> *fast = p;
        while (k && fast->next) {
            k--;
            fast = fast->next;
        }
        if (k) {
            return nullptr;
        }

        while (fast->next) {
            p = p->next;
            fast = fast->next;
        }

        return p->next;
    }

    template<typename T>
    Node<T> *getMin(Node<T> *p) {
        Node<T> *min = p->next;
        while (p->next) {
            if (p->next->data < min->data) {
                min = p->next;
            }
            p = p->next;
        }
        return min;
    }

    template<typename T>
    void ascInsert(Node<T> *p, Node<T> *x) {
        while (p->next) {
            if (x->data < p->next->data) {
                break;
            }
            p = p->next;
        }

        insertBack(p, x);
    }

    template<typename T>
    void deleteNode(Node<T> *p, Node<T> *x) {
        while (p->next) {
            if (x->data == p->next->data) {
                p->next = p->next->next;
            }
            p = p->next;
        }
    }

    void moveAllOdds2Front(INode *p) {
        INode *head = p;
        INode *odds = emptyList<int>();
        INode *oddsTail = odds;
        INode *evens = emptyList<int>();
        INode *evensTail = evens;

        while (p->next) {
            if (p->next->data & 1) {
                oddsTail->next = p->next;
                oddsTail = oddsTail->next;
            } else {
                evensTail->next = p->next;
                evensTail = evensTail->next;
            }
            p = p->next;
        }
        evensTail->next = nullptr;
        oddsTail->next = evens->next;
        head->next = odds->next;
    }
};
#endif //DATASTRUCTCPPDEMO_LIST_H
