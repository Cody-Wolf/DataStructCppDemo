#include <iostream>
#include <algorithm>
#include <random>

#define DEBUG std::cout << "DEBUG" << std::endl

std::mt19937 rnd(20010906);

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
        return out << *node;
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
};

namespace Stack {

    template<typename T>
    Node<T> *emptyStack() {
        return new Node<T>();
    }

    template<typename T>
    void push(Node<T> *top, Node<T> *x) {
        x->next = top->next;
        top->next = x;
    }

    template<typename T>
    Node<T> *pop(Node<T> *top) {
        Node<T> *result = top->next;
        top->next = top->next->next;
        result->next = nullptr;
        return result;
    }

    template<typename T>
    bool isEmpty(Node<T> *top) {
        return !top->next;
    }

    void test() {
        int size = 5;
        INode *stack = List::asList2(new int[size]{0, 1, 2, 3, 4}, size);
        std::cout << "stack : " << stack << std::endl;

        std::cout << "pop from stack " << stack << " : (" << pop(stack)->data << ")" << stack << std::endl;

        std::cout << "push 0 to stack " << stack << " : ";
        push(stack, new INode(0));
        std::cout << stack << std::endl;
    }
};


namespace Tree {
    BINode *BST(int array[], int n) {
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
        auto *stack = Stack::emptyStack<
        typeof root>();

        Stack::push(stack, NodeFactory::create(root));

        while (!Stack::isEmpty(stack)) {
            BINode *top = Stack::pop(stack)->data;
            if (rnd() % 10 < 5) {
                top->left = new BINode(int(rnd()) % top->data);
                Stack::push(stack, NodeFactory::create(top->left));
            }
            if (rnd() % 10 < 5) {
                top->right = new BINode(top->data);
                Stack::push(stack, new Node<BINode *>(top->right));
            }
        }

        return root;
    }

    template<typename T>
    void preorder(BNode<T> *p) {
        auto stack = Stack::emptyStack<
        typeof p>();
        auto out = Stack::emptyStack<
        typeof p>();
        Stack::push(stack, NodeFactory::create(p));

        while (!Stack::isEmpty(stack)) {
            auto *top = Stack::pop(stack)->data;
            if (top) {
                Stack::push(out, NodeFactory::create(top));
                if (top->right) {
                    Stack::push(stack, NodeFactory::create(top->right));
                }
                Stack::push(stack, NodeFactory::create(top->left));
            } else {
                std::cout << Stack::pop(out)->data->data << " ";
            }
        }
    }

    void test() {
        int size = 5;
        int *data = new int[size]{3, 4, 1, 5, 2};
        BINode *root = BST(data, size);
        std::cout << "preorder : ";
        preorder(root);
    }
};


int main() {
//    List::test();
//    Stack::test();
    Tree::test();

    return 0;
}
