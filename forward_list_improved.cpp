#include <iostream>
#include <functional>

template<typename T>
struct Node {
    T data;
    Node<T> *next;
    Node() : data(T()), next(nullptr) {} //Default constructor, nos ayuda a inicializar los nodos 
    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {} // // Node constructor, ths helps us avoid using the -> operator
};

template<typename T>
class ForwardList {
    Node<T>* head;

public:
    ForwardList() : head(nullptr) {}

    ~ForwardList() {
        while(!empty()) {
            pop_front();
        }
    }

    void push_front(T input) {
        Node<T> *newNode = new Node(input, head);
        /* otra manera de hacerlo
        Node* newNode = new Node;
        newNode->data = input;
        newNode->next = head;
        */
        head = newNode;
    }

    Node<T>* getHead() const {
        return head;
    }

    void pop_front() {
        if(!empty()) {
            Node<T> *oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }

    T front() {
        if(!empty()) {
            return head->data;
        }
        throw std::runtime_error("List is empty");
    }

    T back() {
        if(!empty()) {
            Node<T> *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            return temp->data;
        }
        throw std::runtime_error("List is empty");
    }

void push_back(T input) {
    Node<T>* newNode = new Node<T>(input);

    Node<T>* temp = head;
    while (temp && temp->next != nullptr) {
        temp = temp->next;
    }
    if (temp) {
        temp->next = newNode;
    } else {
        head = newNode;
    }
}

void pop_back() {
    if(!empty()) {
        Node<T>* temp = head;
        while (temp && temp->next && temp->next->next != nullptr) {
            temp = temp->next;
        }
        if (temp && temp->next) {
            delete temp->next;
            temp->next = nullptr;
        } else {
            delete head;
            head = nullptr;
        }
    }
}

T operator[](int index) {
    if (index < 0) {
        throw std::out_of_range("Index cannot be negative");
    }

    Node<T>* temp = head;
    int count = 0;

    while (temp != nullptr) {
        if (count == index) {
            return temp->data;
        }
        count++;
        temp = temp->next;
    }

    throw std::out_of_range("Index is out of range");
}

int size() {
    int count = 0;
    Node<T>* temp = head; 
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev; 
            prev = current; 
            current = next; 
        }
        head = prev;
    }

// Merge sort

void sort() {
    if (empty()) {
        throw std::runtime_error("Error: List is empty");
    }

    std::function<Node<T>*(Node<T>*)> mergeSort;
    std::function<Node<T>*(Node<T>*, Node<T>*)> sortedMerge;

    sortedMerge = [&](Node<T>* a, Node<T>* b) -> Node<T>* {
        Node<T>* result = nullptr;

        if (a == nullptr)
            return b;
        else if (b == nullptr)
            return a;

        if (a->data <= b->data) {
            result = a;
            result->next = sortedMerge(a->next, b);
        } else {
            result = b;
            result->next = sortedMerge(a, b->next);
        }
        return result;
    };

    mergeSort = [&](Node<T>* h) -> Node<T>* {
        if (h == nullptr || h->next == nullptr)
            return h;

        Node<T>* slow = h;
        Node<T>* fast = h->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        Node<T>* middle = slow;
        Node<T>* nextOfMiddle = slow->next;

        middle->next = nullptr;

        Node<T>* left = mergeSort(h);
        Node<T>* right = mergeSort(nextOfMiddle);

        Node<T>* sortedList = sortedMerge(left, right);
        return sortedList;
    };

    head = mergeSort(head);
}

    bool empty() {
        return head == nullptr;
    }

    // for making things easier crearemos un print para visualizar la lista
    void print() {
        if (empty()) {
            throw std::runtime_error("Error: List is empty");
        }

        Node<T>* temp = head; 
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};
