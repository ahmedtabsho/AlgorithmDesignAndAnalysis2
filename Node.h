#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
using namespace std;
template <class T>

class Node {
public:
    Node(const T& data = T(), Node<T>* next = NULL) : data(data), next(next){   }
    T data;
    Node<T>* next;
};


#endif // NODE_H_INCLUDED