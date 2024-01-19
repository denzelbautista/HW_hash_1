#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <functional>
#include <cmath>
#include "ForwardList.cpp"


template<typename K, typename V>
class Hash_Table_Set {
    struct Bucket {
        ForwardList<std::pair<K, V>> keyValuePairs;
    };

    Bucket* table;
    size_t size;
    size_t capacity;
    int r;
    long p;
    long a;

    long _hash(K key) {
        // Simple hash function del python template
        return (static_cast<long>(std::hash<K>{}(key) * a) % p) % capacity;
    }


    void _resize(size_t new_capacity) {
        Bucket* new_table = new Bucket[new_capacity];

        // Rehashing de todos los elements en una nueva tabla
        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                K key = current->data.first; 
                long hash_val = _hash(key) % new_capacity;
                new_table[hash_val].keyValuePairs.push_front(current->data);
                current = current->next;
            }
        }

        delete[] table; 
        table = new_table;
        capacity = new_capacity;
    }

    void check_and_resize() {
        if (size >= capacity * r / 100) {
            _resize(capacity * 2); 
        } else if (size < capacity * (100 - r) / 100 && capacity > 1) {
            _resize(capacity / 2);
        }
    }

public:
    Hash_Table_Set(int r = 200) : size(0), capacity(1), r(r), p(2147483647) {
        a = rand() % (p - 1) + 1;
        table = new Bucket[capacity];
    }

    ~Hash_Table_Set() {
        delete[] table;
    }

    void insert(K key, V value) {
        check_and_resize();
        long hash_val = _hash(key);

        auto& bucket = table[hash_val];
        Node<std::pair<K, V>>* current = bucket.keyValuePairs.getHead();
        while (current != nullptr) {
            if (current->data.first == key) {
                current->data.second = value;
                return;
            }
            current = current->next;
        }
        bucket.keyValuePairs.push_front(std::make_pair(key, value));
        ++size;
    }



    V find(K key) {
        long hash_val = _hash(key);
        Node<std::pair<K, V>>* current = table[hash_val].keyValuePairs.getHead();
        while (current != nullptr) {
            if (current->data.first == key) {
                return current->data.second;  
            }
            current = current->next;
        }
        return V();  
    }

    void remove(K key) {
        size_t hash_val = _hash(key);
        Node<std::pair<K, V>>* current = table[hash_val].keyValuePairs.getHead();
        Node<std::pair<K, V>>* prev = nullptr;

        while (current != nullptr && current->data.first != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        --size;
        if (prev == nullptr) {
            // Key is in the first node
            table[hash_val].keyValuePairs.pop_front();
        } else {
            prev->next = current->next;
            delete current;
        }
    }


    size_t length() const {
        return size;
    }

    void print() {
        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                std::cout << current->data.first << ": " << current->data.second << "\n";
                current = current->next;
            }
        }
    }

    K find_min() {
        if (size == 0) {
            throw std::runtime_error("Hash table is empty");
        }

        K min_key = std::numeric_limits<K>::max();  
        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                if (current->data.first < min_key) {
                    min_key = current->data.first;
                }
                current = current->next;
            }
        }
        return min_key;
    }

    K find_max() {
        if (size == 0) {
            throw std::runtime_error("Hash table is empty");
        }

        K max_key = std::numeric_limits<K>::lowest();  /
        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                if (current->data.first > max_key) {
                    max_key = current->data.first;
                }
                current = current->next;
            }
        }
        return max_key;
    }


    K find_next(K key) {
        if (size == 0) {
            throw std::runtime_error("Hash table is empty");
        }

        K next_key = std::numeric_limits<K>::max();
        bool found = false;

        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                if (current->data.first > key && current->data.first < next_key) {
                    next_key = current->data.first;
                    found = true;
                }
                current = current->next;
            }
        }

        if (!found) {
            throw std::runtime_error("Next value not found");
        }
        return next_key;
    }

    K find_prev(K key) {
        if (size == 0) {
            throw std::runtime_error("Hash table is empty");
        }

        K prev_key = std::numeric_limits<K>::lowest();
        bool found = false;

        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                if (current->data.first < key && current->data.first > prev_key) {
                    prev_key = current->data.first;
                    found = true;
                }
                current = current->next;
            }
        }

        if (!found) {
            throw std::runtime_error("Previous value not found");
        }
        return prev_key;
    }


    void iter_order(std::function<void(K, V)> func) {
        if (size == 0) {
            return;
        }

        // Extract all elements
        std::vector<std::pair<K, V>> elements;
        for (size_t i = 0; i < capacity; ++i) {
            Node<std::pair<K, V>>* current = table[i].keyValuePairs.getHead();
            while (current != nullptr) {
                elements.push_back(current->data);
                current = current->next;
            }
        }

        // Sort elements por key
        std::sort(elements.begin(), elements.end(), [](const std::pair<K, V>& a, const std::pair<K, V>& b) {
            return a.first < b.first;
        });

        // Apply the function para todos los elements
        for (const auto& element : elements) {
            func(element.first, element.second);
        }
    }

};

