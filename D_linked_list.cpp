#include <iostream>

using namespace std;

// node made for doubly linked list
struct node
{
    int val;
    node *next;
    node *previous;
    // constructor for node to initialize the values
    explicit node(int val = 0, node *next = nullptr, node *previous = nullptr)
    {
        this->val  = val;
        this->next = next;
        this->previous = previous;
    }
};

class D_Linked_List
{
private:
    // main properties
    node *head;
    node *tail;
    int length;

    // function to link to nodes n1 is first node n2 is the second
    static void link(node *n1, node *n2)
    {
        n1->next = n2;
        n2->previous = n1;
    }

    // function to delete the by its address
    node *delete_node(node *n)
    {
        if (!n) return nullptr;
        node *pre = n->previous;
        node *nxt = n->next;
        delete [] n;
        if (pre && nxt) {
            link(pre, nxt);
        }
        else if (!pre && !nxt) {
            head = nullptr;
            tail = nullptr;
        } else if (!pre) {
            nxt->previous = nullptr;
            head = nxt;
        } else {
            pre->next = nullptr;
            tail = pre;
        }
        length--;
        return pre;
    }

    // insert the first element (the linked list is empty)
    void insert_empty(int val)
    {
        node *newNode = new node(val); // making the node
        head = tail = newNode; // make the new node the head and also the tail of linked list
        length++;
    }

    // insert new node not in the beginning nor end with the node previous it
    void insert_newNode_in_middle(int val, node *prev)
    {
        node *newNode = new node(val);
        node *nxt = prev->next;
        // link it with previous and next also
        link(prev, newNode);
        link(newNode, nxt);
        length++;
    }

public:

    // initiate the linked list
    D_Linked_List()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // print all elements in the linked list
    void print()
    {
        for (auto i = head; i ; i = i->next) {
            cout << i->val << " ";
        }
        cout << "\n";
    }

    // print all elements but from end to beginning
    void print_reversed()
    {
        for (auto i = tail ; i ; i = i->previous)
        {
            cout << i->val << " ";
        }
        cout << "\n";
    }

    // get the current size
    int get_size() const
    {
        return length;
    }

    // check if the array is empty or not
    bool is_empty() const
    {
        return !length;
    }

    // inserting new element at the back of linked list
    void push_back(int val)
    {
        // if the linked list to empty
        if (!length)
        {
            insert_empty(val);
            return;
        }

        node *newNode = new node(val);
        link(tail, newNode);
        tail = newNode;
        length++;
    }

    // inserting in the beginning
    void push_front(int val)
    {
        // if the linked list to empty
        if (!length)
        {
            insert_empty(val);
            return;
        }

        node *newNode = new node(val);
        link(newNode, head);
        head = newNode;
        length++;
    }

    // getting the address of the first node that has the same value
    node *get_node(int val)
    {
        // iterate till reach that node that has the same value
        for (node *it = head; it ; it = it->next) {
            if (it->val == val)
                return it;
        }
        // if not found
        return nullptr;
    }

    // insert element in sorted list and keep it sorted
    void insert_sorted(int val)
    {
        if (is_empty())
        {
            insert_empty(val);
            return;
        }
        if (val <= head->val)
        {
            push_front(val);
            return;
        }
        for (auto i = head->next ; i ; i = i->next) {
            if (val <= i->val)
            {
                insert_newNode_in_middle(val, i->previous);
                return;
            }
        }
        push_back(val);
    }

    // delete the first element
    void pop_front()
    {
        delete_node(head);
    }

    // // delete the last element
    void pop_back()
    {
        delete_node(tail);
    }

    // delete element by its address
    node *pop_node(node *n)
    {
        return delete_node(n);
    }

    // deleting the the first element that has the same value
    void remove(int val)
    {
        for (auto it = head ; it ; it = it->next)
        {
            if (it->val == val)
            {
                delete_node(it);
                return;
            }
        }
    }

    // deleting the the all element that have the same value
    void removeAll(int val)
    {
        int cnt = length;
        auto it = head;
        while (cnt--)
        {
            if (it->val == val)
            {
                it = delete_node(it);
                if (!it)
                {
                    it = head;
                    continue;
                }
            }
            it = it->next;
        }
    }

    // delete elements the even position
    void pop_even()
    {
        auto it = head;
        for (int i = 1, len = length; i <= len; ++i) {
            auto nxt = it->next;
            if (i%2==0)
            {
                delete_node(it);
            }
            it = nxt;
        }
    }

    // delete elements the odd position
    void pop_odd()
    {
        auto it = head;
        for (int i = 1, len = length; i <= len; ++i) {
            auto nxt = it->next;
            if (i%2)
            {
                delete_node(it);
            }
            it = nxt;
        }
    }

    // check if the linked list is palindrome or not
    bool is_palindrome()
    {
        auto left = head;
        auto right = tail;
        for (int i = 0, len = length/2; i < len; ++i) {
            if (left->val != right->val)
                return false;
            left = left->next;
            right = right->previous;
        }
        return true;
    }


    // get the middle node without using length and if length is even get the length/2+1 element
    node *get_middle()
    {
        auto left = head;
        auto right = tail;
        while (left != right && right->previous != left)
        {
            left = left->next;
            right = right->previous;
        }
        return right;
    }

    // reverse the arrangement of the elements
    void reverse()
    {
        for (auto it = head ; it ; it = it->previous)
        {
            swap(it->next, it->previous);
        }
        swap(head, tail);
    }

    // add the element of another sorted linked list to my sorted linked list
    void merge_sorted(D_Linked_List l2)
    {
        // if l2 is empty there is nothing to change
        if (l2.is_empty()) return;
        // if my linked list is empty so we wil insert all elements of l2 one by one
        if (is_empty())
        {
            for (node *it2 =l2.head; it2; it2 = it2->next) {
                push_back(it2->val);
            }
            return;
        }
        node *it2 =l2.head;
        // if the first element in l2 is small to be the new head
        if (it2->val < head->val)
        {
            push_front(it2->val);
            it2 = it2->next;
        }
        // inserting till the end of my linked list
        for (auto it = head ; it && it2 ; it = it->previous)
        {
            if (it2->val < it->val)
            {
                insert_newNode_in_middle(it2->val, it);
                it2 = it2->next;
            }
        }
        // insert the rest elements (that are greater than or equal of last element in my linked list
        while (it2)
        {
            push_back(it2->val);
            it2 = it2->next;
        }
    }


};

int main() {
    D_Linked_List l;
    l.push_back(10);
    l.push_back(20);
    l.push_front(0);
    cout << l.get_size() << "\n";
    l.print();
    l.print_reversed();
    l.insert_sorted(5);
    l.insert_sorted(-1);
    l.insert_sorted(0);
    l.insert_sorted(100);
    l.print();
    l.pop_back();
    l.print();
    l.pop_front();
    l.print();
    l.removeAll(0);
    l.print();
    l.remove(1);
    l.print();
    node *f = l.get_node(0);
    l.pop_node(f);
    l.print();
    l.push_front(-1);
    l.print();
    l.pop_even();
    l.print();
    l.push_back(100);
    l.print();
    l.pop_odd();
    l.print();
    cout << l.is_palindrome() << "\n";
    l.push_front(5);
    l.print();
    cout << l.is_palindrome() << "\n";
    l.push_front(10);
    l.print();
    cout << l.is_palindrome() << "\n";
    node *n = l.get_middle();
    cout << n->val << "\n";
    l.push_back(7);
    l.print();
    n = l.get_middle();
    cout << n->val << "\n";
    l.print();
    l.reverse();
    l.print();
    l.pop_back();
    l.pop_back();
    D_Linked_List l2;
    l2.push_back(5);
    l2.push_back(10);
    l2.push_back(20);
    l.merge_sorted(l2);
    l.print();
    return 0;
}
