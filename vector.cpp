#include <iostream>
#include <assert.h>

using namespace std;

class Vector
{
    /*
     *
     * it is a dynamic array as we call it in cpp vector
     * and other languages like python called list
     * the advantages of the vector is not fixed and so fast like arrays
     * the idea built an array and then if I use extra space in memory when appending an new element
     * I shouldn't put it in a new array but using the extra space and if the actual size is  not enough
     * we put it in lager array
     *
     * */
private:
    int size; // the size if the real size that the user use it
    int *arr = nullptr; // this is the actual vector
    int capacity; // this is an actual size that used to save the time when we append new item

    void expand()
    {
        /*
         * this function is used to expand the actual size of the array
         * used when the capacity is not enough to store all values
         *
         */
        capacity = size * 2 + 5; // the way to expand the capacity and suitable for zero and small numbers
        if (!arr)
        {
            /*
             * if the array has no element (array is pointing to nullptr)
             */
            int *arr2 = new int[capacity] {};
            arr = arr2;
            return;
        }
        int *arr2 = new int[capacity];
        for (int i = 0; i < size; ++i) {
            arr2[i] = arr[i];
        }
        swap(arr, arr2);

        delete [] arr2; // used to delete the old items
    }

    void shift(int &index, int &val)
    {
        /*
         * used to shift elements of the array to right
         * mainly used before inserting new item in the array
         */
        for (int i = size; i > index; --i) {
            arr[i] = arr[i-1];
        }
        arr[index] = val;
    }

public:
    Vector(int size = 0)
    {
        /*
         * constructor used to initialize the size and array
         * all items initialized by zero
         */
        if (size < 0)
            this->size = 1; // if the user enter a wrong size convert it to size 1
        this->size = size;
        expand(); // to initialize all items by zero
    }


    int get(int index)
    {
        /*
         * get the value at this index
         */
        assert(index >= 0 && index < size); // if the size out of range show error
        return arr[index];
    }
    void set(int index, int val)
    {
        /*
         * to change the value in specific index
         */
        assert(index >= 0 && index < size); // if the size out of range show error
        arr[index] = val;
    }

    void print()
    {
        /*
         * print all the elements in the vector
         */
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    int length()
    {
        /*
         * get the real size of the vector
         */
        return size;
    }

    int get_front()
    {
        /*
         * get the value of the first element
         */
        return arr[0];
    }
    int get_back()
    {
        /*
         * get the value of the last element
         */
        return arr[size-1];
    }

    int find(int val)
    {
        /*
         * find the index of the first element that has the value == val
         * if not return -1
         */
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] == val)
                return i;
        }
        return -1;
    }

    void push_back(int val)
    {
        /*
         * add an element at the end of the array
         */
        if (size == capacity)
            expand(); // if the size will be greater than capacity so we expand the size
        arr[size++] = val; // assign new value and increasing the size by 1
    }

    void insert(int index, int val)
    {
        /*
         * add an element at any index and shift all element after that index
         */
        if (size == capacity)
            expand();  // if the size will be greater than capacity so we expand the size
        shift(index, val);
        size++;
    }

    void pop_back()
    {
        /*
         * remove the last element from the vector
         */
        arr[--size] = 0;
    }

    void erase(int index)
    {
        /*
         * remove an element at specific index
         */
        assert(index >= 0 && index < size);
        arr[index] = 0;
        for (int i = index+1; i < size; ++i) {
            // shift left all elements after the removed element to take its new place
            swap(arr[i], arr[i-1]);
        }
        size--;
    }

    void right_rotate()
    {
        /*
         * take the last element and move it to the first place
         */
        for (int i = size-1; i > 0; --i) {
            swap(arr[i], arr[i-1]);
        }
    }

    void left_rotate()
    {
        /*
         * take the first element and move it to the last place
         */
        for (int i = 0, len = size-1; i < len; ++i) {
            swap(arr[i], arr[i+1]);
        }
    }

    void right_rotate(int n)
    {
        /*
         * take the last n elements and move it to the first place by there order
         */
        for (int i = size-n; i > 0; --i) {
            for (int j = 0; j < n; ++j) {
                swap(arr[i+j], arr[i-1+j]);
            }
        }
    }

    int find_transposition(int val)
    {
        /*
         * used to find the element if it is found move it one place to left
         * (increase it priorty) 
         * used at huge vector to find the element move faster every time 
         * ##used if you don't care about changing the order##
         */
        int index = find(val);
        if (index == -1)
            return -1;
        if (index == 0)
            return 0;
        swap(arr[index], arr[index-1]);
        return index-1;
    }

    ~Vector()
    {
        /*
         * it is the destructor 
         * deleting all elements and make array point on nothing
         */
        delete [] arr;
        arr = nullptr;
    }
};

int main() {
//    Vector v(10);
//    for (int i = 0; i < 10; ++i) {
//        v.set(i, i+1);
//    }
//    v.print();
//    cout << v.find(5) << " " << v.find(55) << "\n";

    Vector V(5);
    V.set(0, -1);
    for (int i = 0; i < 10; ++i) {
        V.push_back(i);
    }
    V.insert(4, 100);
    V.insert(V.length(), 5);
    V.print();
    V.right_rotate();
    V.print();
    V.left_rotate();
    V.print();
    V.right_rotate(3);
    V.print();
    V.pop_back();
    V.print();
    V.erase(2);
    V.print();
    V.find_transposition(-1);
    V.print();
    return 0;
}
