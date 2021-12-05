#include <optional>
#include <memory>
#include <iostream>
#include <assert.h>

/// Convenience function that returns an optional from a unique pointer.
/// So that deferencing it while null would result in an exception, not
/// a segmentation fault (which is a potential RCE vulnerability).
template<typename T>
std::optional<std::reference_wrapper<T>> uniquePtrToReference(const std::unique_ptr<T>& pointer) {
    if (pointer.get() != nullptr) {
        return pointer.operator*();
    } else {
        return std::nullopt;
    }
}

/// node that construct the (singly) linked list ;)
struct node{
    int val;
    std::unique_ptr<node> next;
    node(int val = 0)
    {
        // initializing the node values
        this->val = val;

        // unique_ptr auto initializes into null
    }
};

class LinkedList{
private:
    // Modern C++ is about expressing your intent in code
    // So, making "head" as unique_ptr not only managed memory
    // but also expresses your intent that LinkedList "owns"
    // head, so that with the removal of LinkedList from memory
    // head would be automatically removed.
    /// the first node
    std::unique_ptr<node> head;

    // Modern C++ doesn't like pointers (because it is tempting
    // to do arithmetic on it), so, to point to an object you
    // don't own (it would be owned by a "node"), use a "reference"
    // and since C++ references are immutable, use a mutable wrapper
    // and since C++ references are non-nullable, use std::optional.
    // This may lead to cleaner and safer code.
    /// the last node
    std::optional<std::reference_wrapper<node>> tail;
    /// number of elements in the linked list
    int length = 0;

    /// inserting element when the list is empty
    void insert_empty(int val)
    {
        // Modern C++ doesn't like raw pointers, so
        std::unique_ptr<node> newNode = std::make_unique<node>(val);
        head = std::move(newNode);
        tail = uniquePtrToReference(head);
    }

    /// delete if the size of the linked list is 1
    void delete_only_rest_element()
    {
        // Setting a unique_ptr into other value (including nullptr) will remove
        // object from memory automatically
        head = nullptr;
        tail = std::nullopt;
    }

    // get the value of the index from back not front (recursion)
    int get_val_node_from_last(int n, std::optional<std::reference_wrapper<node>> Node) const
    {
        // Modern C++ idiom for getting value from optional after checking it, similar
        // to Swift's "if let" and Kotlin's ".let"
        if (auto node = Node) {
            int out = get_val_node_from_last(n, uniquePtrToReference(Node->get().next)); // recursion till the end
            if (out+1 == n) // if the index == needed index return the value
                return Node->get().val;
            return out+1; // otherwise increase the index and return to the previous node
        } else {
            // base case of the recursion
            return 0;
        }
    }

public:
    // function to get the size of linked list
    int get_size() const
    {
        return length;
    }

    // print all elements of the array
    void print() const
    {
        auto it = uniquePtrToReference(head);
        // print the value of the node until reach null
        while (it != std::nullopt)
        {
            std::cout << it->get().val << " ";
            it = uniquePtrToReference(it->get().next);
        }
        std::cout << "\n";
    }

    // insert new element at the end of the linked list
    void insert_end(int val)
    {
        // check if the linked list is empty or not to do suitable way
        if (length)
        {
            std::unique_ptr<node> newNode = std::make_unique<node>(val);
            tail->get().next = std::move(newNode);
            tail = uniquePtrToReference(tail->get().next);
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
            std::unique_ptr<node> newNode = std::make_unique<node>(val);
            newNode->next = std::move(head);
            head = std::move(newNode);
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
            auto tmp = std::move(head);
            head = std::move(tmp->next);
            // tmp is auto deleted, due to use of unique_ptr
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
            tail = tmp;
            // A node owns its next, so setting it to null would remove it
            // from memory, so getting the tail through getting the next
            // of the before last element then removing it would automatically
            // remove it from memory.
            tail->get().next = nullptr;
        }
        length--;
    }

    // delete all elements at the linked list
    void clear()
    {
        auto tmp = std::move(head);
        for (int i = 0; i < length; ++i) {
            head = std::move(tmp);
            tmp = std::move(head->next);
        }
        head = nullptr;
        tail = std::nullopt;
        length = 0;
    }

    // get the node of index i
    std::optional<std::reference_wrapper<node>> get_ith(int i) const
    {
        // if the out of range return null
        if(i < 0 && i >= length)
            return std::nullopt;
        // iterate until reach the node
        auto it = uniquePtrToReference(head);
        for (int j = 0; j < i; ++j) {
            if (it != std::nullopt) {
                it = uniquePtrToReference(it->get().next);
            } else {
                return std::nullopt;
            }
        }
        return it;
    }

    // get the index of element from last
    int get_back(int n) const
    {
        assert(n > 0 && n <= length && length);
        return get_val_node_from_last(n, uniquePtrToReference(head));
    }
    // get the index of the value val
    int find(int val) const
    {
        auto it = uniquePtrToReference(head);
        int counter = 0; // the index of the current node
        // iterate till reach the same value
        while (it)
        {
            if (it->get().val == val)
                return counter;
            it = uniquePtrToReference(it->get().next);
            counter++;
        }
        // if not found return -1
        return -1;
    }

    // find the value and decrease its index by 1
    int improved_find(int val) const
    {
        auto it = uniquePtrToReference(head);
        // check if empty
        if (!head)
            return -1;
        // check if it is already first elemnt
        if (head->val == val)
            return 0;
        int counter = 0;
        // iterate on the linked until reach the elment
        while (it->get().next)
        {
            if (it->get().next->val == val)
            {
                std::swap(it->get().val, it->get().next->val);
                return counter;
            }

            it = uniquePtrToReference(it->get().next);
            counter++;
        }
        // if not fount return -1
        return -1;
    }

    // compare two linked lists by the size
    bool is_same_size(const LinkedList &l2) const
    {
        return this->length == l2.length;
    }
};

using namespace std;

int main() {
    LinkedList l;
    l.insert_end(10);
    l.insert_end(20);
    l.insert_end(50);
    l.print();
    cout << l.get_size() << "\n";
    auto n1 = l.get_ith(1);
    cout << n1->get().val << " " << n1->get().next->val << "\n";
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
    auto l2 = std::make_unique<LinkedList>();
    cout << l.is_same_size(l2.operator*()) << "\n";
    l2->insert_front(1);
    l2->insert_front(2);
    cout << l.is_same_size(l2.operator*()) << "\n";
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
