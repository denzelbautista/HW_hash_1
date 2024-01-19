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

    bool Contains(T data) const {
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
        Set result;
        Node<int>* temp = keys.getHead();
        while (temp != nullptr) {
            result.Insert(table.at(temp->data));
            temp = temp->next;
        }
        temp = other.keys.getHead();
        while (temp != nullptr) {
            result.Insert(other.table.at(temp->data));
            temp = temp->next;
        }
        return result;
    }

    Set Intersect(const Set &other) {
        Set result;
        Node<int>* temp = keys.getHead();
        while (temp != nullptr) {
            if (other.Contains(table.at(temp->data))) {
                result.Insert(table.at(temp->data));
            }
            temp = temp->next;
        }
        return result;
    }

    Set Difference(const Set &other) {
        Set result;
        Node<int>* temp = keys.getHead();
        while (temp != nullptr) {
            if (!other.Contains(table.at(temp->data))) {
                result.Insert(table.at(temp->data));
            }
            temp = temp->next;
        }
        return result;
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

    // Prueba de inserción
    std::cout << "Insertando elementos: 8, 2, 3, 0" << std::endl;
    mySet.Insert(8);
    mySet.Insert(2);
    mySet.Insert(3);
    mySet.Insert(0);
    std::cout << "Conjunto despues de inserciones: ";
    mySet.Print();

    // Prueba de contención
    std::cout << "Contiene 8? " << (mySet.Contains(8) ? "Si" : "No") << std::endl;
    std::cout << "Contiene 5? " << (mySet.Contains(5) ? "Si" : "No") << std::endl;

    // Prueba de eliminación
    std::cout << "Eliminando elemento 2" << std::endl;
    mySet.Remove(2);
    std::cout << "Conjunto despues de eliminar el elemento 2: ";
    mySet.Print();

    // Verificar si un elemento eliminado ya no está
    std::cout << "Contiene 2? " << (mySet.Contains(2) ? "Si" : "No") << std::endl;


    // Creating another set for testing
    Set<int> anotherSet;
    anotherSet.Insert(3);
    anotherSet.Insert(4);
    anotherSet.Insert(5);
    std::cout << "Another set: ";
    anotherSet.Print();

    Set<int> unionSet = mySet.Union(anotherSet);
    std::cout << "Union de los 2 sets: ";
    unionSet.Print();

    Set<int> intersectSet = mySet.Intersect(anotherSet);
    std::cout << "Intersection de los 2 sets: ";
    intersectSet.Print();

    Set<int> differenceSet = mySet.Difference(anotherSet);
    std::cout << "Difference de los 2 sets: ";
    differenceSet.Print();

    return 0;
}
