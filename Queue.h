#ifndef QUEUE_H_
#define QUEUE_H_

template <class T>
class linkQueue
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T &x, node *N = NULL)
        {
            data = x;
            next = N;
        }
        node() : next(NULL) {}
        ~node() {}
    };
    node *front, *rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
};

#endif