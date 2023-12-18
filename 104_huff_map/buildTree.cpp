#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t ql;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      ql.push(new Node(i, counts[i]));
    }
  }

  if (ql.size() == 0) {
    return NULL;
  }

  while (ql.size() > 1) {
    Node * ls = ql.top();
    ql.pop();
    Node * rs = ql.top();
    ql.pop();
    ql.push(new Node(ls, rs));
  }
  return ql.top();
  //WRITE ME!
}
