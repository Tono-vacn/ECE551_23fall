#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(5);
    il.addFront(4);
    assert(il[0] == 4);
    assert(il.getSize() == 2);
    // WRITE ME
  }
  void testAddBack() {
    IntList il;
    il.addBack(6);
    il.addBack(7);
    il.addBack(8);
    assert(il.getSize() == 3);
    assert(il[0] == 6);
    assert(il[1] == 7);
    assert(il[2] == 8);
  }

  void frontBack() {
    IntList il;
    for (int i = 3; i < 5; i++) {
      il.addBack(i);
    }
    for (int i = 0; i < 3; i++) {
      il.addFront(2 - i);
    }
    assert(il.getSize() == 5 && il[0] == 0 && il[1] == 1 && il[2] == 2 && il[3] == 3 &&
           il[4] == 4);
    assert(il.head->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == 0 && il.head->next->data == 1 &&
           il.head->next->next->data == 2 && il.head->next->next->next->data == 3 &&
           il.head->next->next->next->next->data == 4);
    assert(il.tail->data == 4 && il.tail->prev->data == 3 &&
           il.tail->prev->prev->data == 2 && il.tail->prev->prev->prev->data == 1 &&
           il.tail->prev->prev->prev->prev->data == 0);
    assert(il.find(0) == 0 && il.find(1) == 1 && il.find(2) == 2 && il.find(3) == 3 &&
           il.find(4) == 4);
    assert(il.remove(-1) == false);
  }
  //assert(il.tail)

  void testRemove() {
    IntList il;
    il.addBack(9);
    il.addBack(10);
    assert(il.remove(9) == true);
    assert(il.remove(0) == false);
    assert(il.getSize() == 1);
  }

  void testCopy() {
    IntList il;
    il.addBack(1);
    il.addFront(5);
    //[1,5]
    IntList nl = IntList(il);
    //Int
  }

  // many more tester methods
  void testComplex() {
    IntList il;
    assert(il.getSize() == 0 && il.head == NULL && il.tail == NULL);
    //addback
    il.addFront(2);
    assert(il.getSize() == 1 && il.head == il.tail && il.head != NULL &&
           il.tail != NULL && il.head->data == 2 && il.head->next == NULL &&
           il.head->prev == NULL);
    //addfront [2,1]
    il.addBack(1);
    assert(il.getSize() == 2 && il.head->data == 2 && il.head->next->data == 1 &&
           il.tail->data == 1 && il.head->prev == NULL && il.tail->next == NULL &&
           il.head->next->prev == il.head);
    //remove [2]
    bool res = il.remove(1);
    assert(res == true && il.getSize() == 1 && il.head == il.tail && il.head != NULL &&
           il.head->data == 2);

    //addagain [10,2]
    il.addFront(10);
    assert(il.getSize() == 2 && il.head->data == 10 && il.tail->data == 2 &&
           il.head->next == il.tail && il.head->next->data == 2 &&
           il.head->prev == NULL && il.tail->next == NULL &&
           il.head->next->prev == il.head);
    //index
    assert(il[0] == 10 && il[1] == 2);
    assert(il.find(10) == 0 && il.find(2) == 1);

    //= [10,2]
    IntList testil = il;
    assert(testil.getSize() == 2 && testil.head->data == 10 && testil.tail->data == 2 &&
           testil.head->next == testil.tail && testil.head->next->data == 2 &&
           testil.head->prev == NULL && testil.tail->next == NULL &&
           testil.head->next->prev == testil.head);

    //remove again [2]
    bool fal = il.remove(5);
    assert(fal == false);
    bool suc = il.remove(10);
    assert(suc == true && il.getSize() == 1 && il.head == il.tail && il.head != NULL &&
           il.head->data == 2);
    //new il [2]
    IntList newil = IntList(il);
    assert(newil.getSize() == 1 && newil.head == newil.tail && newil.head != NULL &&
           newil.head->data == 2);

    //remove again []
    bool suc2 = newil.remove(2);
    assert(suc2 == true && newil.getSize() == 0 && newil.head == NULL &&
           newil.tail == NULL && newil.remove(10) == false);

    newil.addBack(1);
    assert(newil.head == newil.tail && newil.head->data == 1 &&
           newil.head->prev == NULL && newil.head->next == NULL && newil.getSize() == 1 &&
           newil.find(1) == 0 && newil[0] == 1);

    newil.addFront(1);
    assert(newil.getSize() == 2 && newil.find(1) == 0 && newil.head->data == 1 &&
           newil.head->next->data == 1 && newil.tail->data == 1 && newil[1] == 1 &&
           newil[0] == 1 && newil.remove(5) == false && newil.find(2) == -1);

    //[20,100,2]
    il.addFront(100);
    il.addFront(20);
    assert(il.find(100) == 1 && il.find(20) == 0 && il.find(2) == 2 && il[0] == 20 &&
           il[2] == 2 && il[1] == 100);

    //remove middle [20,2]
    bool suc3 = il.remove(100);
    bool fal2 = il.remove(100);
    assert(suc3 == true && fal2 == false && il.head->data == 20 && il.tail->data == 2 &&
           il.getSize() == 2 && il.head->next->next == NULL &&
           il.tail->prev->prev == NULL && il.head->next->prev == il.head &&
           il.tail->prev->next == il.tail);

    //newil [20,2]
    newil = il;
    assert(newil.head->data == 20 && newil.tail->data == 2 && newil.getSize() == 2 &&
           newil.head->next->next == NULL && newil.tail->prev->prev == NULL &&
           newil.head->next->prev == newil.head && newil.tail->prev->next == newil.tail);

    //newil [20]
    bool suc4 = newil.remove(2);
    assert(suc4 == true);
    assert(newil.getSize() == 1 && newil.head == newil.tail);
    assert(newil.head->data == 20);
    assert(newil.head->prev == NULL && newil.tail->next == NULL);

    //[20,20]
    newil.addBack(20);
    bool suc5 = newil.remove(20);
    assert(suc5 == true);
    assert(newil.getSize() == 1 && newil.head == newil.tail);
    assert(newil.head->data == 20);
    assert(newil.head->prev == NULL && newil.tail->next == NULL);

    //[]
    bool suc6 = newil.remove(20);
    assert(suc6);
    assert(newil.getSize() == 0 && newil.head == NULL && newil.tail == NULL);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testRemove();
  t.testAddBack();
  t.frontBack();
  t.testCopy();
  t.testComplex();
  //t.frontBack();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
