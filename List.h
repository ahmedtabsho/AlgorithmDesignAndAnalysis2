#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>
#include "Node.h"
using namespace std;

//bagli liste sinifi

template <class T>
class List{
private:
    Node<T>* root;
    Node<T>* tail;
    int length;
public:
    List();// kurucu fonksiyon
    List(const List<T>& rhs);// kopylama fonksiyonu
    List<T>& operator=(const List<T>& rhs);// atama operatoru asiri yuklenmsi
    List<T>& assign(const List<T>& rhs);// kopylama fonksiyonu
    ~List();// yikici fonksiyon
    void clear();// listeyi temizleyen fonksiyon
    bool isEmpty() const;// listenin bos olup olmadigini kontrol eden fonksiyon
    Node<T>* begin() const;// ilk elemani donduren
    Node<T>* end() const;// son elemani donduren
    int size();// listenin boyutu
    void push_back(const T& value);// listenin sonuna eleman ekleyen
    T& getBack();// listenin son elemanini getiren
    T& front();// listenin ilk elemanini getiren
    void pop_back();// listenin son elemani silen
    void pop_front();// listenin ilk elemani silen
    void print() const;// listenin elemanlarini yazdiran
};


#endif // LIST_H_INCLUDED