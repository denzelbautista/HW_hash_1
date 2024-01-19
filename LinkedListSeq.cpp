#include <iostream>
#include <functional>

template<typename A, typename T>
struct Linked_List_Node {
    T x;
    A key;
    Linked_List_Node<A, T> *next;
    Linked_List_Node(A k) : x(T()), next(nullptr), key(k) {}
    //Linked_List_Node(A k, T x) : x(x), next(nullptr), key(k) {}
    Linked_List_Node(A k, T x, Linked_List_Node<A, T>* next = nullptr) : x(x), next(next), key(k) {}
};

template<typename A, typename T>
class Linked_List_Seq {
    Linked_List_Node<A, T>* head;

public:
    Linked_List_Seq() : head(nullptr) {}

    ~Linked_List_Seq() {
        while(!empty()) {
            delete_first();
        }
    }

    void insert_first(A key, T input) {
        Linked_List_Node<A, T> *newLinked_List_Node = new Linked_List_Node(key, input, head);
        head = newLinked_List_Node;
    }

    void delete_first() {
        if(!empty()) {
            Linked_List_Node<A, T> *oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }

    T front() {
        if(!empty()) {
            return head->x;
        }
        throw std::runtime_error("List is empty");
    }

    T back() {
        if(!empty()) {
            Linked_List_Node<A, T> *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            return temp->x;
        }
        throw std::runtime_error("List is empty");
    }

    void insert_last(A key_, T input_) {
        Linked_List_Node<A, T>* newLinked_List_Node = new Linked_List_Node<A, T>(key_, input_);

        Linked_List_Node<A, T>* temp = head;
        while (temp && temp->next != nullptr) {
            temp = temp->next;
        }
        if (temp) {
            temp->next = newLinked_List_Node;
        } else {
            head = newLinked_List_Node;
        }
    }

    void delete_last() {
        if(!empty()) {
            Linked_List_Node<A, T>* temp = head;
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

    T get_at(int index) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        Linked_List_Node<A, T>* temp = head;
        int count = 0;

        while (temp != nullptr) {
            if (count == index) {
                return temp->x;
            }
            count++;
            temp = temp->next;
        }

        throw std::out_of_range("Index is out of range");
    }

    void set_at(int index, T value) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        Linked_List_Node<A, T>* temp = head;
        for (int count = 0; temp != nullptr; count++) {
            if (count == index) {
                temp->x = value; 
                return;
            }
            temp = temp->next;
        }
        
        throw std::out_of_range("Index is out of range");
    }


    void insert_at(int index, A key, T value) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        if (index == 0) {
            insert_first(key, value);
            return;
        }

        if (get(key) == nullptr){
            throw std::out_of_range("Key already exists");
        }

        Linked_List_Node<A, T>* temp = head;
        for (int count = 0; temp != nullptr && count < index - 1; count++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            throw std::out_of_range("Index is out of range");
        }

        Linked_List_Node<A, T>* newLinked_List_Node = new Linked_List_Node<A, T>(key, value, temp->next);
        temp->next = newLinked_List_Node;
    }

    void delete_at(int index) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }

        if (index == 0) {
            if (head == nullptr) {
                throw std::out_of_range("Index is out of range");
            }
            Linked_List_Node<A, T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Linked_List_Node<A, T>* temp = head;
        for (int count = 0; temp != nullptr && count < index - 1; count++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            throw std::out_of_range("Index is out of range");
        }

        Linked_List_Node<A, T>* Linked_List_NodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete Linked_List_NodeToDelete;
    }

    int size() {
        int count = 0;
        Linked_List_Node<A, T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void clear() {
        while(!empty()) {
            delete_first();
        }
    }

    void reverse() {
        Linked_List_Node<A, T>* prev = nullptr;
        Linked_List_Node<A, T>* current = head;
        Linked_List_Node<A, T>* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    bool empty() {
        return head == nullptr;
    }

    void print() {
        if (empty()) {
            throw std::runtime_error("Error: List is empty");
        }

        Linked_List_Node<A, T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->key << ":" << temp->x << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    Linked_List_Node<A, T>* get(A key_){
        Linked_List_Node<A, T>* temp = head;
        while (temp != nullptr){
            if (temp->key == key_){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void set (A key_, T value){
        Linked_List_Node<A, T>* temp = head;
        while (temp != nullptr){
            if (temp->key == key_){
                temp->x = value;
                return;
            }
            temp = temp->next;
        }
        insert_last(key_, value);
    }
};




int main(){
    Linked_List_Seq<char, int> list;
    list.insert_first('a', 10);
    list.insert_first('b', 9);
    list.insert_first('c', 8);
    list.insert_first('d', 7);
    list.insert_first('e', 6);
    list.insert_first('f', 5);
    list.insert_first('g', 4);
    list.insert_first('h', 3);
    list.insert_first('i', 2);
    list.insert_first('j', 1);
    list.print();
    list.delete_at(3);
    list.print();
    list.insert_at(4, 'j', 3);
    list.print();
    list.set_at(3, 4);
    list.print();
    std::cout << list.get_at(3) << std::endl;
    std::cout << list.size() << std::endl;
    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;
    list.print();
    std::cout << list.get('a')->x << std::endl;
    list.set('a', 50);
    std::cout << list.get('a')->x << std::endl;
    list.clear();
    std::cout << list.empty() << std::endl;
    return 0;
}
