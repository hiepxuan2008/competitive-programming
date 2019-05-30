// Problem: Imeplement Stack using Array
// Solution: Mai Thanh Hiep

#include <iostream>
using namespace std;

class Stack {
    const int DEFAULT_CAPACITY = 10;
    int _capacity;
    int* _arr;
    int _size;

    void enlarge_capacity() {
        // double capacity
        _capacity = _capacity * 2;
        int* newArr = new int[_capacity];

        // copy old array to new array
        for (int i = 0; i < _size; i++)
            newArr[i] = _arr[i];

        // delete old array
        delete[]_arr;

        // assign _arr to new array
        _arr = newArr;
    }

public:
    Stack(int capacity) {
        _capacity = capacity;
        _arr = new int[_capacity];
        _size = 0;
    }

    Stack() : Stack(DEFAULT_CAPACITY) {
    }

    int top() {
        if (empty())
            throw "Stack is empty";

        return _arr[_size - 1];
    }

    void push(int value) {
        if (_size == _capacity) {
            enlarge_capacity();
        }

        _arr[_size++] = value;
    }

    int pop() {
        if (_size == 0) {
            throw "Stack empty before pop";
        }

        int value = _arr[--_size];
        return value;
    }

    int size() {
        return _size;
    }

    bool empty() {
        return _size == 0;
    }

    ~Stack() {
        delete[] _arr;
    }
};

int main() {
    Stack mystack(2);
    mystack.push(1);
    mystack.push(2);
    mystack.push(3);
    cout << mystack.top() << endl;
    mystack.push(4);
    mystack.push(5);
    mystack.pop();
    mystack.pop();
    mystack.push(6);
    cout << mystack.top() << endl;

    return 0;
}
