#include <iostream>
#include <algorithm>
#include "../include/node/Node.h"
#include "../include/node/BNode.h"
#include "../include/List.h"
#include "../include/Stack.h"
#include "../include/Tree.h"

#define DEBUG std::cout << "DEBUG" << std::endl

namespace List {
    void test() {
        int size = 5;
        int *asc = new int[size]{0, 1, 1, 2, 4};
        int *rnd = new int[size]{3, 2, 5, 1, 4};

        INode *ascList = asList(asc, size);
        INode *randList = asList(rnd, size);

        std::cout << "asc list : " << *ascList << std::endl;
        std::cout << "rand list : " << *randList << std::endl;

        std::cout << "find 3th in " << *ascList << " : " << getKth(ascList, 3)->data << std::endl;
        std::cout << "find last 4th in " << *randList << " : " << getLastKth(randList, 4)->data << std::endl;

        std::cout << "find min in " << *randList << " : " << getMin(randList)->data << std::endl;

        INode *tmp = copyOf(ascList);
        std::cout << "insert 1 and 3 into " << *tmp << " : ";
        ascInsert(tmp, new INode(3));
        ascInsert(tmp, new INode(1));
        std::cout << *tmp << std::endl;

        delete tmp;
        tmp = copyOf(ascList);
        std::cout << "delete all min value in " << *tmp << " : ";
        deleteNode(tmp, getMin(tmp));
        std::cout << *tmp << std::endl;

        delete tmp;
        tmp = copyOf(randList);
        std::cout << "move all odds number to front of list  " << *tmp << " : ";
        moveAllOdds2Front(tmp);
        std::cout << *tmp << std::endl;
    }
}

namespace Stack {
    void test() {
        int size = 5;
        INode *stack = List::asList2(new int[size]{0, 1, 2, 3, 4}, size);
        std::cout << "stack : " << stack << std::endl;

        std::cout << "pop from stack " << stack << " : (" << pop(stack) << ")" << stack << std::endl;

        std::cout << "push 0 to stack " << stack << " : ";
        push(stack, 0);
        std::cout << stack << std::endl;
    }
}

namespace Tree {
    void test() {
        int size = 7;
        int *data = new int[size]{4, 2, 6, 1, 3, 5, 7};
        BINode *root = BST(data, size);

        std::cout << "preorder : ";
        preorder(root);
        std::cout << std::endl;

        std::cout << "inorder : ";
        inorder(root);
        std::cout << std::endl;

        std::cout << "postorder : ";
        postorder(root);
        std::cout << std::endl;

    }
};


int main() {
//    List::test();
//    Stack::test();
    Tree::test();

    return 0;
}
