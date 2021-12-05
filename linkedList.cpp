#include <iostream>
#include <assert.h>

using namespace std;
// node that construct the (singly) linked list ;)
struct node{
    int val;
    node *next;
    node(int val = 0)
    {
        // initializing the node values
        this->val = val;
        next = nullptr;
    }
};

class Linked_List{
private:
    // the first node
    node *head = nullptr;
    // the last node
    node *tail = nullptr;
    // number of elements in the linked list
    int length = 0;

    // inserting element when the list is empty
    void insert_empty(int val)
    {
        node *newNode = new node(val);
        head = newNode;
        tail = newNode;
    }
    // delete if the size of the linked list is 1
    void delete_only_rest_element()
    {
        delete [] head;
        head = nullptr;
        tail = nullptr;
    }

    // get the value of the index from back not front (recursion)
    int get_val_node_from_last(int n, node* Node)
    {
        if (Node == nullptr) // base case
            return 0;
        int out = get_val_node_from_last(n, Node->next); // recursion till the end
        if (out+1 == n) // if the index == needed index return the value
            return Node->val;
        return out+1; // otherwise increase the index and return to the previous node
    }

public:
    // function to get the size of linked list
    int get_size() const
    {
        return length;
    }

    // print all elements of the array
    void print()
    {
        auto it = head;
        // print the value of the node until reach null
        while (it != nullptr)
        {
            cout << it->val << " ";
            it = it->next;
        }
        cout << "\n";
    }

    // insert new element at the end of the linked list
    void insert_end(int val)
    {
        // check if the linked list is empty or not to do suitable way
        if (length)
        {
            node *newNode = new node(val);
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            insert_empty(val);
        }
        length++;
    }

    // insert new element at the start of the linked list
    void insert_front(int val)
    {
        // check if the linked list is empty or not to do suitable way
        if (length)
        {
            node *newNode = new node(val);
            newNode->next = head;
            head = newNode;
        } else
        {
            insert_empty(val);
        }
        length++;
    }

    // deleting the first element
    void delete_front()
    {
        // check if already the linked list is empty
        if (!length) return;
        // check if the linked list has one elemnt or not to do suitable way
        if (length == 1)
        {
            delete_only_rest_element();
        }
        else
        {
            auto tmp = head;
            head = head->next;
            delete [] tmp;
        }
        length--;
    }

    // delete the last element at the linked list
    void delete_back()
    {
        // check if it already is empty or not
        if (!length) return;
        // check if the linked list has one elemnt or not to do suitable way
        if (length == 1)
        {
            delete_only_rest_element();
        }
        else
        {
            auto tmp = get_ith(length-2);
            delete [] tail;
            tail = tmp;
            tail->next = nullptr;
        }
        length--;
    }

    // delete all elements at the linked list
    void clear()
    {
        auto tmp = head;
        for (int i = 0; i < length; ++i) {
            delete [] head;
            head = tmp;
            tmp = tmp->next;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // get the node of index i
    node *get_ith(int i)
    {
        // if the out of range return null
        if(i < 0 && i >= length)
            return nullptr;
        // iterate until reach the node
        auto it = head;
        for (int j = 0; j < i; ++j) {
            it = it->next;
        }
        return it;
    }

    // get the index of element from last
    int get_back(int n)
    {
        assert(n > 0 && n <= length && length);
        return get_val_node_from_last(n, head);
    }
    // get the index of the value val
    int find(int val)
    {
        auto it = head;
        int counter = 0; // the index of the current node
        // iterate till reach the same value
        while (it)
        {
            if (it->val == val)
                return counter;
            it = it->next;
            counter++;
        }
        // if not found return -1
        return -1;
    }

    // find the value and decrease its index by 1
    int improved_find(int val)
    {
        auto it = head;
        // check if empty
        if (!head)
            return -1;
        // check if it is already first elemnt
        if (head->val == val)
            return 0;
        int counter = 0;
        // iterate on the linked until reach the elment
        while (it->next)
        {
            if (it->next->val == val)
            {
                swap(it->val, it->next->val);
                return counter;
            }

            it = it->next;
            counter++;
        }
        // if not fount return -1
        return -1;
    }

    // compare two linked lists by the size
    bool is_same_size(Linked_List *l2)
    {
        return this->length == l2->length;
    }

    // destory the linked list
    ~Linked_List()
    {
        // traverse to delete
        while (head != nullptr)
        {
            auto tmp = head->next;
            delete [] head;
            head = tmp;
        }
        tail= nullptr;
    }
};

int main() {
    Linked_List l;
    l.insert_end(10);
    l.insert_end(20);
    l.insert_end(50);
    l.print();
    cout << l.get_size() << "\n";
    node *n1 = l.get_ith(1);
    cout << n1->val << " " << n1->next->val << "\n";
    cout << l.find(10) << "\n";
    cout << l.find(0) << "\n";
    cout << l.improved_find(20) <<"\n";
    l.print();
    cout << l.improved_find(20) << "\n";
    cout << l.improved_find(100) << "\n";
    l.print();
    l.insert_front(5);
    cout << l.get_size() << "\n";
    l.print();
    for (int i = 0; i < 2; ++i) {
        l.delete_front();
    }
    cout << l.get_size() << "\n";
    l.print();
    cout << l.get_back(2)<<'\n';
    auto *l2 = new Linked_List;
    cout << l.is_same_size(l2) << "\n";
    l2->insert_front(1);
    l2->insert_front(2);
    cout << l.is_same_size(l2) << "\n";
    cout << l.get_size() << "\n";
    l.print();
    l.delete_back();
    cout << l.get_size() << "\n";
    l.print();
    l.delete_back();
    cout << l.get_size() << "\n";
    l.print();
    l.insert_front(10);
    l.insert_front(0);
    l.insert_end(20);
    l.print();
    l.clear();
    l.print();
    l.clear();
    l.print();


    return 0;
}
