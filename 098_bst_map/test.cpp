#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map;
  map.add(60, 1);
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  std::cout << "\n";
  int ans1 = map.lookup(60);
  int ans2 = map.lookup(35);
  map.remove(19);
  //map.inorder();
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";

  map.remove(60);
  //map.inorder();
  std::cout << "\n";

  map.remove(1);
  //map.inorder();
  std::cout << "\n";

  map.remove(25);
  //map.inorder();
  std::cout << "\n";

  map.remove(11);
  //map.inorder();
  std::cout << "\n";

  BstMap<int, int> map2 = map;
  //map2.inorder();
  std::cout << "\n";
  return EXIT_SUCCESS;
}
