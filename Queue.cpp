#include <iostream>
#include "Queue.h"
using namespace std;

template <class T>
linkQueue<T>::linkQueue()
{
    front = rear = NULL;
}

template <class T>
linkQueue<T>::~linkQueue()
{
    node *tmp;
    while (front != NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class T>
bool linkQueue<T>::isEmpty() const
{
    return front == NULL;
}

template <class T>
T linkQueue<T>::getHead() const
{
    return front->data;
}

template <class T>
void linkQueue<T>::enQueue(const T &x)
{
    if (rear == NULL)
        front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

template <class T>
T linkQueue<T>::deQueue()
{
    node *tmp = front;
    T value = front->data;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    delete tmp;
    return value;
}