#include <iostream>
#include <assert.h>
using namespace std;

struct node
{
    int val;
    int index;
    node* next;
    node* previous;
    node(int val, int index)
    {
        this->val = val;
        this->index = index;
        next = nullptr;
        previous = nullptr;
    }
};

class Array_linked_list
{
private:
    node *head;
    node *tail;
    int actual_length;
    int array_length;

    void link(node *n1, node *n2) {
        n1->next = n2;
        n2->previous = n1;

    }

    void insert_when_empty(int val, int index)
    {
        node *newNode = new node(val, index);
        head = tail = newNode;
        actual_length++;
    }

    void insert_between(node *nBefore, node *nAfter, node *n)
    {
        link(nBefore, n);
        link(n, nAfter);
        actual_length++;
    }

public:
    explicit Array_linked_list(int size)
    {
        head = nullptr;
        tail = nullptr;
        actual_length = 0;
        array_length = size;
    }

    void set_value(int val, int index)
    {
        assert(index >= 0 && index < array_length);
        if (actual_length == 0)
        {
            insert_when_empty(val, index);
            return;
        }

        node *newNode = new node(val, index);
        if (index < head->index)
        {
            link(newNode, head);
            head = newNode;
            return;
        }

        for (auto it = head->next; it ; it = it->next) {
            if (index < it->index)
            {
                insert_between(it->previous, it, newNode);
                return;
            }
            if (index == it->index)
            {
                it->val = val;
                return;
            }
        }

        link(tail, newNode);
        tail = newNode;
        actual_length++;
    }

    void print()
    {
        auto it = head;
        for (int i = 0; i < array_length; ++i) {
            if (it && it->index == i)
            {
                cout << it->val << " ";
                it = it->next;
            }
            else
                cout << "0 ";
        }
        cout << '\n';
    }

    void print_exact_list()
    {
        for (auto it = head ; it ; it = it->next) {
            cout << it->val << " ";
        }
        cout << "\n";
    }

    void add(Array_linked_list *al2)
    {
        if (al2->actual_length == 0)
        {
            return;
        }
        auto it1 = head;
        auto it2 = al2->head;
        node *newNode = new node(it2->val, it2->index);
        if (it2->index < it1->index)
        {
            link(newNode, head);
            head = newNode;
        } else if (it2->index == it1->index)
        {
            head->val += it2->val;
        }
        it2 = it2->next;
        for (; it2 && it1 ; ) {
            if (it2->index < it1->index)
            {
                newNode = new node(it2->val, it2->index);
                insert_between(it1->previous, it1, newNode);
                it2 = it2->next;
            }
            else if (it2->index == it1->index)
            {
                it1->val += it2->val;
                it2 = it2->next;
            }else
            {
                it1 = it1->next;
            }
        }
        while (it2)
        {
            newNode = new node(it2->val, it2->index);
            link(tail, newNode);
            tail = newNode;
            actual_length++;
        }

    }
    
};

struct node_M{
    Array_linked_list *row;
    int index;
    node_M *next;
    node_M *previous;
    node_M(Array_linked_list *row = nullptr, int index = 0)
    {
        this->row = row;
        this->index = index;
        next = nullptr;
        previous = nullptr;
    }
};

class Matrix_linked_list {
private:
    node_M *head;
    node_M *tail;
    int actual_length;
    int row_length;
    int width;

    void link(node_M *n1, node_M *n2)
    {
        n1->next = n2;
        n2->previous = n1;
    }

    node_M *make_new_row(int val, int row, int column)
    {
        auto new_all = new  Array_linked_list(width);
        new_all->set_value(val, column);
        auto new_node = new node_M(new_all, row);
        actual_length++;
        return new_node;
    }

    void insert_empty(int val, int row, int column)
    {
        auto new_node = make_new_row(val, row, column);
        head = new_node;
        tail = new_node;
        actual_length++;
    }

public:
    Matrix_linked_list(int rows_size, int columns_size)
    {
        head = nullptr;
        tail = nullptr;
        actual_length = 0;
        row_length = rows_size;
        width = columns_size;
    }

    void set_value(int val, int row, int column)
    {
        assert(row >= 0 && row < row_length);
        if (actual_length == 0)
        {
            insert_empty(val, row, column);
            return;
        }
        if (row < head->index)
        {
            node_M *new_node = make_new_row(val, row, column);
            link(new_node, head);
            head = new_node;
            return;
        }
        for (auto it = head ; it ; it = it->next) {
            if (row < it->index){
                node_M *new_node = make_new_row(val, row, column);
                link(it->previous, new_node);
                link(new_node, it);
                return;
            } else if (row == it->index) {
                it->row->set_value(val, column);
                return;
            }
        }
        node_M *new_node = make_new_row(val, row, column);
        link(tail, new_node);
        tail = new_node;
    }

    void print()
    {
        auto it = head;
        for (int i = 0; i < row_length; ++i) {
            if (it && it->index == i)
            {
                it->row->print();
                it = it->next;
            } else{
                for (int j = 0; j < width; ++j) {
                    cout << "0 ";
                }
                cout << '\n';
            }
        }
        cout << '\n';
    }

    void print_exact()
    {
        for (auto it = head ; it ; it= it->next)
        {
            it->row->print_exact_list();
        }
        cout << '\n';
    }


};

int main() {
    /*Array_linked_list *al = new Array_linked_list(10);
    al->set_value(10, 1);
    al->set_value(90, 9);
    al->set_value(50, 5);
    al->set_value(0, 0);
    al->print();
    al->print_exact_list();
    Array_linked_list *al2 = new Array_linked_list(10);
    al2->set_value(5, 5);
    al2->set_value(1, 0);
    al->add(al2);
    al->print();*/
    /*auto all = new Array_linked_list(5);
    all->set_value(5, 1);
    all->print();*/

    auto mll = new Matrix_linked_list(10, 5);
    mll->print();
    mll->set_value(5, 1, 1);
    cout << '\n';
    mll->print();
    mll->set_value(10, 9, 4);
    cout << "\n";
    mll->print();
    mll->print_exact();

    return 0;
}
