#include "Hash_Table_Set.cpp"

template<typename T>
class Set
{
private:
    Hash_Table_Set<int, T> table;
    ForwardList<int> keys;
    int key_count = 0;
public:
    Set(){}
    void Insert(T data){
        if (keys.getHead() == nullptr){
            table.insert(key_count, data);
            keys.push_back(key_count);
            key_count++;
            return;
        }

        Node<T>* temp = keys.getHead();
        int count = 0;

        while (temp != nullptr){
            if (table.find(temp->data) == data){
                return;
            }
            if (table.find(temp->data) > data){
                keys.insert_at(count, key_count);
                table.insert(key_count, data);
                key_count++;
                return;
            }
            count++;
            temp = temp->next;
        }

        keys.push_back(key_count);
        table.insert(key_count, data);
        key_count++;
    }
    bool Remove(T data){
        if (keys.getHead() == nullptr || Contains(data) == false){
            return false;
        }

        Node<T>* temp = keys.getHead();
        int count = 0;

        while (temp != nullptr){
            if (table.find(temp->data) == data){
                table.remove(keys[count]);
                keys.delete_at(count);
                return true;
            }
            count++;
            temp = temp->next;
        }

    }
    bool Contains(T data){
        return table.find(data) == T() ? true : false;
    }
    Set Union(const Set &other){}
    Set Intersect(const Set &other){}
    Set Difference(const Set &other){}
    ~Set(){}
};

int main(){
    Set<int> x;
    x.Insert(8);
    x.Insert(2);
    x.Insert(3);
    x.Insert(0);


    std::cout << x.Contains(8) << " " << x.Contains(2) << " " << x.Contains(3) << std::endl;

    return 0;
}