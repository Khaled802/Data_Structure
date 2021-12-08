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

    // reverse the linked list by recursion
    node *rec_rev(node *it_end, int &count)
    {
        // base case: when reach the last node
        if (!it_end->next) return head;
        // recursion and get the start one
        node *start = rec_rev(it_end->next, count);
        if (count > 1)
        {
            node *tmp = it_end->next;
            it_end->next = start;
            node *startNext = start->next;
            start->next = tmp->next;
            tmp->next = startNext;
            count-=2;
        }
        return start;
    }
    // delete the node by the the adress node before it
    void delete_node(node *node_before)
    {
        // if there is no node before it that mean that the node is front
        if (!node_before) {delete_front(); length --; return;}
        // if the it is not front and size 1 something wrong if length = 0 there is no thing to delete
        if (length < 2)
            return;
        // reusing the delete_back if the node is last one
        if (node_before->next == tail) delete_back();
        else
        {
            node *remove = node_before->next;
            // link before and after with each other
            node_before->next = remove->next;
            // delete wanted node 
            delete [] remove;
            length--; // update the length
        }

    }
    
    // get the next node to link reversed part
    node * pNode = nullptr;
    //reverse first k nodes by recursion
    node *reverse_nodes_rec(int k, node *it)
    {
        if (k == 1)
        {
            pNode = it;
            return it->next;
        }
        node *last = reverse_nodes_rec(k-1, it->next);
        it->next->next = it;
        return last;
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
    bool is_same_size(Linked_List *l2) const
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

    // hyper functions ....

    // delete the first node has the same value of val
    void delete_with_key(int val)
    {
        node *j = nullptr;
        for (auto i = head ; i ; i = i->next)
        {
            if (i->val == val)
            {
                if (i == head)
                {
                    delete_front();
                } else if (i == tail)
                {
                    delete_back();
                }
                else
                {
                    j->next = i->next;
                    delete [] i;
                    length--;
                }
                return;
            }
            j = i;
        }
    }

    // swap every two pairs -no overlap-
    void swap_pairs() {
        auto it = head;
        while (it && it->next)
        {
            swap(it->val, it->next->val);
            it = it->next->next;
        }
    }
    
    // delete the nodes with even pos (2, 4, 6, ..)
    void delete_even_position()
    {
        node *it = head;
        node *pre = head;
        int size = length;
        for (unsigned int i = 1; i <= size; ++i) {
            if (i&1)
            {
                pre = it;
                it = it->next;
                continue;
            }
            if (it == tail)
                delete_back();
            else
            {
                pre->next = it->next;
                delete [] it;
                length--;
                it = pre->next;
            }
        }
    }
    
    // revers the hole linked list
    void reverse()
    {
        int size = length;
        node *h = head;
        rec_rev(h, size);
        swap(head, tail);
    }

    // insert the enement at its position when the linked list is sorted
    void insert_sorted(int val)
    {
        if (val <= head->val)
        {
            insert_front(val);
            return;
        }

        for (node *i = head ; i->next ; i=i->next) {
            if (val <= i->next->val && val >= i->val)
            {
                // making new node
                node *newNode = new node(val);
                // inserting it
                node *nextNode = i->next;
                i->next = newNode;
                newNode->next = nextNode;
                length++;
                return;
            }
        }
        insert_end(val);
    }
    
    // swaping the head and tail by its node not only values
    void swap_head_tail()
    {
        if (length < 2) return;
        node *secondNode = head->next;
        node *secondLast = head;
        while (secondLast->next->next) secondLast = secondLast->next;
        swap(head, tail);
        secondLast->next = tail;
        head->next = secondNode;
        tail->next = nullptr;
    }

    // take first k nodes and move them to the end
    void left_rotate(int k)
    {
        if (k >= length) return;
        node *last = head;
        while (--k)
        {
            last = last->next;
        }
        tail->next = head;
        tail = last;
        head = last->next;
        last->next = nullptr;
    }

    // delete duplicated values
    void delete_duplicated()
    {
        if (length < 2) return;
        for (auto i = head; i->next ; i = i->next) {
            for (auto j = i; j->next ; j = j->next) {
                if (i->val == j->next->val)
                {
                    delete_node(j);
                }
            }
        }
    }

    // delete last element that has the same value = val
    void delete_last(int val)
    {
        // there is no thing to remove
        if (!length) return;
        // if there is only one element
        if (length == 1)
        {
            if (head->val == val)
            {
                // handle deleting the rest element
                delete_only_rest_element();
                length--;
            }
            return;
        }
        node *last_node = nullptr;
        // iterate to get the pre last node that has value = val
        for (auto i = head; i->next ; i = i->next)
        {
            if (i->next->val == val)
                last_node = i;
        }
        // if the node has value go and delete the next 
        // but if not there is two states if the is no node its value = val 
        // or it is the first element at the linked list
        if (last_node)
        {
            delete_node(last_node);
            return;
        }
        else
        {
            if (val == head->val)
                delete_front();
        }
    }

    // move all node its value = val to the end of the linked list
    void move_back(int val)
    {
        if (length < 2) return;
        int counter= 0;
        // this for repeat numbers may it will be the hole linked list is has this value
        while (head->val == val && counter < length)
        {
            node *new_head = head->next;
            tail->next = head;
            tail = head;
            tail->next = nullptr;
            head = new_head;
            counter++;
        }
        for (auto i = head; i->next->next && i->next && i; i = i->next)
        {
            if (i->next->val == val)
            {
                node *moved = i->next;
                i->next = moved->next;
                tail->next = moved;
                tail = moved;
                tail->next = nullptr;

            }
        }
    }

    // getting max node by recursion
    int get_max(node *it = nullptr)
    {
        assert(head != nullptr);
        if (it == nullptr) it = head;
        if (it->next == nullptr) return it->val;
        return max(get_max(it->next), it->val);
    }

    // splitting the linked list evens and odds and re connecting them again
    void split_odd_even_pos()
    {
        if (length <= 2) return;
        auto it = head;
        for (unsigned int i = 0, len = length-1; i < len; ++i) {
            if (i&1) continue;
            auto move = it->next;
            it->next = move->next;

            tail->next = move;
            tail = move;
            move->next = nullptr;
            it = it->next;
        }
    }

    // inserting elements in l2 but each after the alternating of it
    void insert_alternating(Linked_List *l2)
    {
        auto it1 = head;
        node *it2 = l2->head;
        while (it2 && it1)
        {
            auto third_node = it1->next;
            auto new_node = new node(it2->val);
            it1->next = new_node;
            new_node->next = third_node;
            it1 = third_node;
            if (!third_node)
                tail = new_node;
            it2 = it2->next;
            length++;
        }
        while (it2)
        {
            insert_end(it2->val);
            it2 = it2->next;
        }
    }

    // used when linked list used as a number holder and sum it with other one
    void add_num(Linked_List *l)
    {
        auto it1 = head;
        node *it2 = l->head;
        int res = 0;
        while (it1 && it2)
        {
            int sum = it1->val + it2->val + res;
            res = sum / 10;
            it1->val = sum % 10;
            it1 = it1->next;
            it2 = it2->next;
        }

        if (it1 && res)
        {
            insert_end(res);
        }
        while (it2)
        {
            insert_end(res+it2->val);
            res = 0;
            it2 = it2->next;
        }
    }
    
    // reverse first part of the linked list
    void reverse_chain(int k)
    {
        assert(k <= length && length >= 0);
        if (k <= 1) return;
        auto it = head;
        pNode = nullptr;
        auto last = reverse_nodes_rec(k, it);
        head->next = last;
        head = pNode;

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
    l.insert_end(50);
    l.insert_end(60);
    l.insert_front(40);
    l.print();
    l.delete_with_key(60);
    l.print();
    l.delete_with_key(40);
    l.print();
    l.delete_with_key(80);
    l.print();
    l.delete_back();
    l.delete_with_key(50);
    l.print();
    l.insert_front(10);
    l.swap_pairs();
    l.print();
    l.insert_front(20);
    l.print();
    l.swap_pairs();
    l.print();
    l.insert_front(10);
    l.insert_end(70);
    l.print();
    l.delete_even_position();
    l.print();
    l.delete_even_position();
    l.print();
    l.delete_even_position();
    l.print();
    l.insert_end(5);
    l.insert_end(1);
    l.print();
    l.reverse();
    l.print();
    l.insert_sorted(2);
    l.print();
    l.insert_sorted(0);
    l.print();
    l.insert_sorted(100);
    l.print();
    l.insert_sorted(5);
    l.print();
    l.swap_head_tail();
    l.print();
    l.left_rotate(1);
    l.print();
    l.left_rotate(6);
    l.print();
    l.delete_duplicated();
    l.print();
    l.insert_front(0);
    l.print();
    l.delete_last(0);
    l.print();
    l.delete_last(0);
    l.print();
    l.move_back(100);
    l.print();
    l.move_back(100);
    l.print();
    l2->print();
    l2->move_back(2);
    l2->print();
    l2->delete_front();
    l2->insert_front(2);
    l2->insert_front(2);
    l2->print();

    cout << l.get_max() << "\n";
    cout << l2->get_max() << "\n";
    l.print();

    l.split_odd_even_pos();
    l.print();
    l2->delete_front();
    cout << l2->get_size() << "\n";
    l2->print();

    l2->split_odd_even_pos();
    l2->print();
    l.insert_alternating(l2);
    l.print();
    cout << l.get_size() << "\n";
    l.print();
    l2->print();
    l2->add_num(&l);
    l2->print();
    l.reverse_chain(l.get_size());
    l.print();

    return 0;
}
