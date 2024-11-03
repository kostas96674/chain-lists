//
// Created by Dimitris on 09/05/2021.
//

#ifndef ERGASIA_CHAIN_H
#define ERGASIA_CHAIN_H

#include <iostream>

using namespace std;

template <class T>
class ChainNode;

template <class T>
class Chain {

public:
    Chain() { first = 0; } // constructor
    ~Chain(); // destructor
    bool IsEmpty() const { return first == 0; }
    int Length() const;
    bool Find(int k, T& x) const;
    int Search(const T& x) const; // int Chain<T>::Search(const T& x) const
    Chain<T>& Delete(int k);
    Chain<T>& Insert(int k, const T& x);
    void Output(ostream& out) const;

private:
    ChainNode<T> *first;  // pointer to first node

};

template <class T>
class ChainNode {

    friend Chain<T>;

private:
    T data;
    ChainNode<T> *link;

};

template<class T>
Chain<T>::~Chain() { // Chain constructor. Delete all nodes in chain.

    ChainNode<T> *next; // next node

    while(first) { // while(first != 0)

        next = first->link;
        delete first;
        first = next;

    }

}

template<class T>
int Chain<T>::Length() const { // Return the number of elements in the chain.

    ChainNode<T> *current = first;
    int len = 0;

    while(current) { // while(current != 0)

        len++;
        current = current->link;

    }

    return len;

}

template<class T>
bool Chain<T>::Find(int k, T& x) const { // Set to x the k'th element from the chain.
                                         // Return false if no k'th, otherwise return true.
    if(k < 1)
        return false;

    ChainNode<T> *current = first;
    int i = 1; // index of current

    while(i < k && current) { // while(i < k && current != 0)

        current = current->link;
        i++;

    }

    if(current) {

        x = current->data;
        return true;

    }

    return false; // no k'th element

}

template<class T>
int Chain<T>::Search(const T& x) const { // Locate x. Return position of x if found.
                                         // Return 0 if x not in the chain.
    ChainNode<T> *current = first;
    int i = 1; // index of current

    while(current && current->data != x) { // while(current != 0 && current->data != x)

        current = current->link;
        i++;

    }

    if(current)
        return i;

    return 0;

}

template<class T>
Chain<T>& Chain<T>::Delete(int k) { // Delete the k'th element.
                                    // Throw out_of_range exception if no k'th element.
    if(k < 1 || !first) // if(k < 1 || first == 0)
        throw out_of_range("Invalid element location in Delete."); // no k'th

    ChainNode<T> *p = first; // p will eventually point to k'th node

    if(k == 1) // p already at k'th
        first = first->link; // second node becomes the first node

    else { // use q to get to k-1'st

        ChainNode<T> *q = first;

        for(int i=1; i<k-1 && q; ++i) // for(int i=1; i<k && q!=0; i++)
            q = q->link;

        if(!q || !q->link) // if(q == 0 || q->link == 0)
            throw out_of_range("Invalid element location in Delete."); // no k'th

        p = q->link; // k'th
        q->link = p->link; // The link of k-1'th node will shows the k+1'th node.

    }

    delete p;
    return *this;

}

template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x) { // Insert x after the k'th element.
    // Throw out_of_range exception if no k'th element.
    if (k < 0)
        throw out_of_range("Invalid element location in Insert.");

    ChainNode<T> *p = first; // p will eventually point to k'th node

    for (int i = 1; i < k && p; ++i)
        p = p->link; // move p to k'th

    if(k > 0 && !p)
        throw out_of_range("Invalid element location in Insert."); // no k'th

    auto *y = new ChainNode<T>; // ChainNode<T> *y = new ChainNode<T>;
    y->data = x;

    if(k) { // insert after p

        y->link = p->link;
        p->link = y;

    } else { // insert as first element

        y->link = first;
        first = y;

    }

    return *this;

}

template<class T>
void Chain<T>::Output(ostream& out) const {

    ChainNode<T> *current;

    for(current = first; current; current = current->link)
        out << current->data << " ";

}

template<class T> // overload <<
ostream& operator<<(ostream& out, const Chain<T>& x) {

    x.Output(out);
    return out;

}

#endif //ERGASIA_CHAIN_H
