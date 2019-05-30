// Problem: Imeplement Queue using Array
// Solution: Mai Thanh Hiep

#include <iostream>
using namespace std;

class Queue {
    const int DEFAULT_CAPACITY = 10;
    int _capacity;
    int* _arr;
    int _top, _tail;
    int _size;

    void enlarge_capacity() {
        // double capacity
        _capacity = _capacity * 2;
        int* newArr = new int[_capacity];

        // copy old array to new array
        for (int i = _top; i < _tail; i++)
            newArr[i] = _arr[i];

        // delete old array
        delete[]_arr;

        // assign _arr to new array
        _arr = newArr;
    }

public:
    Queue(int capacity) {
        _capacity = capacity;
        _arr = new int[_capacity];
        _top = _tail = 0;
        _size = 0;
    }

    Queue() : Queue(DEFAULT_CAPACITY) {
    }

    int top() {
        return _arr[_top];
    }

    void push(int value) {
        if (_size == _capacity) {
            enlarge_capacity();
        }

        _arr[_tail++] = value;
        _size++;
    }

    int pop() {
        if (_size == 0) {
            throw "Queue empty before pop";
        }
        
        int value = _arr[_top++];
        _size--;
        return value;
    }

    int size() {
        return _size;
    }

    bool empty() {
        return _size == 0;
    }

    ~Queue() {
        delete[] _arr;
    }
};

int main() {
    Queue myqueue(2);
    myqueue.push(1);
    myqueue.push(2);
    myqueue.push(3);
    cout << myqueue.top() << endl;
    myqueue.push(4);
    myqueue.push(5);
    myqueue.pop();
    myqueue.pop();
    myqueue.push(6);
    cout << myqueue.top() << endl;

    return 0;
}
