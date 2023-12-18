#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(T d) : data(d), next(NULL), prev(NULL){};
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    Node * cur = rhs.head;
    while (cur != NULL) {
      addBack(cur->data);
      cur = cur->next;
    }
  };
  LinkedList & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      LinkedList newl(rhs);
      Node * tempHead;
      Node * tempTail;
      int tempsz;
      tempHead = newl.head;
      newl.head = this->head;
      this->head = tempHead;

      tempTail = newl.tail;
      newl.tail = this->tail;
      this->tail = tempTail;

      tempsz = newl.size;
      newl.size = this->size;
      this->size = tempsz;
    }
    return *this;
  };
  ~LinkedList() {
    Node * cur = head;
    Node * nextcur = NULL;
    while (cur != NULL) {
      nextcur = cur->next;
      delete cur;
      cur = nextcur;
    }
  };
  void addFront(const T & item) {
    Node * newNode = new Node(item);
    newNode->next = head;
    if (head == NULL) {
      tail = newNode;
    }
    else {
      head->prev = newNode;
    }
    head = newNode;
    size++;
  };
  void addBack(const T & item) {
    Node * newNode = new Node(item);
    newNode->prev = tail;
    if (tail == NULL) {
      head = newNode;
    }
    else {
      tail->next = newNode;
    }
    tail = newNode;
    size++;
  };
  bool remove(const T & item) {
    Node * cur = head;
    while (cur != NULL && cur->data != item) {
      cur = cur->next;
    }
    if (cur != NULL) {
      Node * nextNode = cur->next;
      Node * prevNode = cur->prev;
      if (nextNode != NULL) {
        nextNode->prev = prevNode;
      }
      else {
        tail = prevNode;
      }
      if (prevNode != NULL) {
        prevNode->next = nextNode;
      }
      else {
        head = nextNode;
      }
      delete cur;
      size--;
      return true;
    }
    else {
      return false;
    }
  };
  T & operator[](int index) {
    //try{
    if (index < 0 || index > size - 1 || head == NULL) {
      throw std::exception();
    }
    Node * cur = head;
    for (int i = 0; i < index; i++) {
      cur = cur->next;
      if (cur == NULL) {
        throw std::exception();
      }
    }
    return cur->data;
    //}catch(){
  };
  const T & operator[](int index) const {
    if (index < 0 || index > size - 1 || head == NULL) {
      throw std::exception();
    }
    Node * cur = head;
    for (int i = 0; i < index; i++) {
      cur = cur->next;
      if (cur == NULL) {
        throw std::exception();
      }
    }
    return cur->data;
  };
  int find(const T & item) const {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  };
  int getSize() const { return size; };
  friend void testList(void);
};
//YOUR CODE GOES HERE

#endif
