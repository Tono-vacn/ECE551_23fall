#ifndef _BSTMAP_H__
#define _BSTMAP_H__

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V val;
    Node * left;
    Node * right;
    Node() : key(0), val(0), left(NULL), right(NULL) {}
    Node(const K k, const V v) : key(k), val(v), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { root = mapCopy(rhs.root); }
  Node * mapCopy(Node * cur) {
    if (cur == NULL) {
      return NULL;
    }
    Node * root = new Node(cur->key, cur->val);
    root->left = mapCopy(cur->left);
    root->right = mapCopy(cur->right);
    return root;
  }

  void freeMap(Node * cur) {
    if (cur != NULL) {
      freeMap(cur->right);
      freeMap(cur->left);
      delete cur;
      cur = NULL;
    }
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      freeMap(root);
      root = NULL;
      root = mapCopy(rhs.root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * cur = root;
      while (cur != NULL) {
        if (key > cur->key) {
          if (cur->right == NULL) {
            cur->right = new Node(key, value);
            return;
          }
          else {
            cur = cur->right;
          }
        }
        else if (key < cur->key) {
          if (cur->left == NULL) {
            cur->left = new Node(key, value);
            return;
          }
          else {
            cur = cur->left;
          }
        }
        else {
          cur->val = value;
          return;
        }
      }
    }
  }

  // Node * getNode(Node * cur, const K & k) const {
  //  if (cur != NULL) {
  //  if (k == cur->key) {
  //    return cur;
  //  }
  //  else if (k > cur->key) {
  //    return getNode(cur->right, k);
  //  }
  //   else {
  //    return getNode(cur->left, k);
  //  }
  //}
  //else {
  //return NULL;
  //}
  //}

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    //Node * tar = getNode(root, key);
    //if (tar == NULL) {
    //throw std::invalid_argument("key invalid");
    //}
    //else {
    //return tar->val;
    //}

    Node * cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
        return cur->val;
      }
      else if (key < cur->key) {
        cur = cur->left;
      }
      else {
        cur = cur->right;
      }
    }
    throw std::invalid_argument("invalid key");
  }
  //Node * getMinNode(Node * cur) {
  //assert(cur != NULL);
  //Node * pre = cur;
  //while (cur != NULL) {
  //rec = cur->key;
  //  pre = cur;
  //  cur = cur->left;
  //}
  //return pre;
  //}
  Node * getRemoveNode(Node * cur, const K & k) {
    if (cur == NULL) {
      return cur;
    }
    if (cur->key == k) {
      if (cur->left == NULL) {
        Node * temp = cur->right;
        delete cur;
        return temp;
      }
      else if (cur->right == NULL) {
        Node * temp = cur->left;
        delete cur;
        return temp;
      }
      else {
        //Node * minnode = getMinNode(cur->right);
        //Node * rec = cur;
        Node * itr = cur->right;
        //Node * pre = NULL;
        //Node * pre = cur->right;
        while (itr->left != NULL) {
          //pre = itr;
          itr = itr->left;
        }
        K kr = itr->key;
        V vr = itr->val;
        //V vr = lookup(kr);
        cur->right = getRemoveNode(cur->right, kr);
        //if (pre != NULL) {
        //pre->left = itr->right;
        //}
        //delete itr;
        cur->key = kr;
        cur->val = vr;
        return cur;
        //  rec->key = itr->key;
        //const V vl = itr->val;
        //rec->val = cur->val;
        //Node * temp = itr->right;
        //delete cur;
        //pre->left = temp;
        //add(rec->key, vl);
        //return rec;
        //V minval = lookup(minkey);
      }
    }
    else if (k < cur->key) {
      cur->left = getRemoveNode(cur->left, k);
      return cur;
    }
    else {
      cur->right = getRemoveNode(cur->right, k);
      return cur;
    }
  }

  virtual void remove(const K & key) {
    root = getRemoveNode(root, key);
    //  Node ** cur = &root;
    //Node * temp = NULL;

    //while (*cur != NULL) {
    //if ((*cur)->key == key) {
    //  if ((*cur)->left == NULL) {
    //    temp = (*cur)->right;
    //    delete *cur;
    //    *cur = temp;
    //  }
    //  else if ((*cur)->right == NULL) {
    //    temp = (*cur)->left;
    //    delete *cur;
    //    *cur = temp;
    //  }
    //  else {
    //    Node ** r = cur;
    //    cur = &((*cur)->left);
    //    while ((*cur)->right != NULL) {
    //      cur = &((*cur)->right);
    //    }
    //    (*r)->key = (*cur)->key;
    //    const V vl = (*cur)->val;
    //   temp = (*cur)->left;
    //      delete *cur;
    //    *cur = temp;
    //    add((*r)->key, vl);
    //  }
    //}
    //else if (key < (*cur)->key) {
    //  cur = &(*cur)->left;
    //}
    //else {
    //  cur = &(*cur)->right;
    //}
    //}
  }

  //void inorder() { inorder_print(root); }

  //void inorder_print(Node * root) {
  //if (root != NULL) {
  //  inorder_print(root->left);
  //  std::cout << root->key << " ";
  //  inorder_print(root->right);
  //}
  //}

  virtual ~BstMap<K, V>() {
    freeMap(root);
    root = NULL;
  }
  //return root->value;
  //Node * tar = getNode(root,key);
};

#endif
