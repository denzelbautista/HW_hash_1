#include "HashTableSet.cpp"

template<typename T>
class Set {
private:
    Hash_Table_Set<int, T> table;
    ForwardList<int> keys;
    int key_count = 0;

public:
    Set() {}

    void Insert(T data) {
        if (!Contains(data)) {
            table.insert(key_count, data);
            keys.push_back(key_count);
            key_count++;
        }
    }

    bool Remove(T data) {
        Node<int>* temp = keys.getHead();
        int count = 0;

        while (temp != nullptr) {
            if (table.find(temp->data) == data) {
                table.remove(temp->data);
                keys.delete_at(count);
                return true;
            }
            count++;
            temp = temp->next;
        }
        return false;
    }

    bool Contains(T data) {
        Node<int>* temp = keys.getHead();
        while (temp != nullptr) {
            if (table.find(temp->data) == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    Set Union(const Set &other) {
    }


    Set Intersect(const Set &other) {
    }

    Set Difference(const Set &other) {
    }


    void Print() {
        Node<int>* temp = keys.getHead();
        while (temp != nullptr) {
            std::cout << table.find(temp->data) << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~Set() {}
};

int main() {
    Set<int> mySet;

    // Iinserción
    std::cout << "Insertando elementos: 8, 2, 3, 0" << std::endl;
    mySet.Insert(8);
    mySet.Insert(2);
    mySet.Insert(3);
    mySet.Insert(0);
    std::cout << "Conjunto después de inserciones: ";
    mySet.Print();

    // Contención
    std::cout << "Contiene 8? " << (mySet.Contains(8) ? "Sí" : "No") << std::endl;
    std::cout << "Contiene 5? " << (mySet.Contains(5) ? "Sí" : "No") << std::endl;

    // Eliminación
    std::cout << "Eliminando elemento 2" << std::endl;
    mySet.Remove(2);
    std::cout << "Conjunto después de eliminar el elemento 2: ";
    mySet.Print();

    // Verificación
    std::cout << "Contiene 2? " << (mySet.Contains(2) ? "Sí" : "No") << std::endl;



    return 0;
}
