#include "List.h"

template <class T>
List<T>::List() {
        length = 0;
        root = new Node<T>();
        tail = root;
}

template <class T>
List<T>::List(const List<T>& rhs) : List(){
        *this = rhs;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rhs){  assign(rhs);  }

template <class T>
List<T>& List<T>::assign(const List<T>& rhs){
        clear();
        Node<T>* tmp = rhs.begin();
        while(tmp != rhs.end()){
            push_back(tmp->data);
            tmp = tmp->next;
        }
        return *this;
}

template <class T>
List<T>::~List(){
        clear();
        delete root;
}

template <class T>
void List<T>::clear(){
        while(length > 0)
            pop_front();
}

template <class T>
bool List<T>::isEmpty() const {  return begin() == end();  }

template <class T>
Node<T>* List<T>::begin() const { return root->next; }

template <class T>
Node<T>* List<T>::end() const {  return tail->next;  }

template <class T>
int List<T>::size() {  return length;  }

template <class T>
void List<T>::push_back(const T& value){
        tail->next = new Node<T>(value);
        tail = tail->next;
        length++;
}

template <class T>
T& List<T>::getBack(){
        if(isEmpty())
            throw "yapi bostur...";
        return tail->data;
}

template <class T>
T& List<T>::front(){

        if(isEmpty())
            throw "yapi bostur...";

        return root->next->data;
}

template <class T>
void List<T>::pop_back(){
        Node<T>* tmp = root;
        if(isEmpty())
            throw "yapi bostur....";
        while(tmp->next->next != end())
            tmp = tmp->next;
        delete tail;
        tail = tmp;
        length--;
}

template <class T>
void List<T>::pop_front(){
        Node<T>* tmp = root;
        if(isEmpty())
            throw "yapi bostur....";
        root = tmp->next;
        delete tmp;
        length--;
}


template <class T>
void List<T>::print() const{
        Node<T>* tmp = begin();
        while(tmp != end()){
            cout << tmp->data << "  " ;
            tmp = tmp->next;
        }
        cout << endl;
}