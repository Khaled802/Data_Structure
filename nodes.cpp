#include <iostream>

using namespace std;

struct node{
    /*
     * node consist of two values one is the value
     * second is the addres of the next node
     */
    int val;
    node *next;
    node(int val)
    {
        // constructor used to assign the valued of the node and initialize the next by null
        this->val = val;
        this->next = nullptr;
    }
};

void print(node *n)
{
    /*
     * print the all nodes
     * the final node is its next = null
     */
    while (n != nullptr)
    {
        cout << n->val << " ";
        n = n->next;
    }
    cout << "\n";
}
void printR(node *n)
{
    /*
     * printing all nodes recursively
     */
    if (n == nullptr)
    {
        cout << "\n";
        return;
    }

    cout << n->val << " ";
    print(n->next);
}

void printReversed(node *n)
{
    /*
     * print all values from the last node to the first
     * Recursively
     */
    if (n == nullptr)
        return;
    printReversed(n->next);
    cout << n->val << " ";
}

int find(node *n, int val)
{
    /*
     * find recursively the index of the first node that has the same value
     * but cannot be found return -1
     */
    if (n == nullptr)
        return -1; // if you don't find the value in the hole nodes return -1
    if (n->val == val)
        return 0; // if find the value assign the index to zero for the current node
    int f = find(n->next, val);
    if (f == -1)
        return -1; // if the value is not at hole nodes
    // updating the index referred to the current node
    return 1+f;

}

int main() {
    // assigning the new node with value 10
    node n1(10);
    // print the value of n1
    cout << n1.val << "\n";
    // assigning the new node with value 10
    node n2(20);
    // linking n2 with n1 by making n1 arrow n2 (n1-->n2)
    n1.next = &n2;
    //showing how t
    cout << n1.next->val << "\n";
    // print the value of n1
    node n3(30);
    // link the node 3 with the node2 to make (n1-->n2-->n3)
    n2.next = &n3;
    // printing the value of n3 by n1
    cout << n1.next->next->val << "\n";
    print(&n1);
    printR(&n1);
    printReversed(&n1);
    cout << "\n";
    int x = 10;
    // find the index starting from n2
    cout << find(&n2, x) << "\n";
    cout << find(&n1, x+10) << "\n";
    x = 50;
    cout << find(&n1, x)<<"\n";
    return 0;
}
