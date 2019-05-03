#include "bTree.hpp"
#include <string>
#include <iostream>

int main()
{

#if 1
  bTree<int, std::string> numeric;
  numeric.insert(4, "four");

  numeric.insert(2, "two");
  numeric.insert(6, "six");

  numeric.insert(1, "one");
  numeric.insert(3, "three");

  numeric.insert(5, "five");
  numeric.insert(7, "seven");

  for (int i = 1; i < 8; ++i)
  {
    auto deli = numeric;
    deli.del(i);
    std::cout << "del" << i << ":";
    deli.forEach([](const int &key, std::string &val) {
      std::cout << val;
    });
    std::cout << std::endl;
  }
#endif
#if 0
bTree<int, int> tree;
  // bTree<std::string, int> lkv;
tree.insert(2, 2);
tree.insert(1, 1);
tree.insert(3, 3);
tree.del(3);
// tree.del(3);

tree.forEach([](const int &key, int &val){
  std::cout << "  Key: " << key << std::endl;
    std::cout << "  Val: " << val << std::endl;
});
#endif

#if 0

  bTree<std::string, bTree<std::string, int> > outer;
  bTree<std::string, int> lkv;
 
  //populate an LKV  
  std::cout << "Inserting" << std::endl;
  lkv.insert("one", 1);
  lkv.insert("three", 3);
  lkv.insert("four", 4);
  lkv.insert("two", 2);
  auto ptr = lkv.get("a");
  if(!ptr)
    std::cout << "success" << std::endl;
  else
    std::cout << "death" << std::endl;
  

  std::cout << "/****************** TEST 1 DONE *****************************/" << std::endl;

  //put two copies map into outer
  outer.insert("outer1", lkv);
  outer.insert("outer2", lkv);
  std::cout << "/****************** TEST 2 DONE *****************************/" << std::endl;

  //iterate over outer then inner
  std::cout << std::endl << std::endl << "Full iteration:" << std::endl;
  outer.forEach([](const std::string &key, bTree<std::string, int> &val){
    std::cout << key << std::endl;
    val.forEach([](const std::string &key, int &val){
      std::cout << "  Key: " << key << std::endl;
      std::cout << "  Val: " << val << std::endl;
    });
  });
  std::cout << "/****************** TEST 3 DONE *****************************/" << std::endl;

  //make a copy of one LKV, delete an item, then iterate
  std::cout << std::endl << std::endl << "Deleted item \"three\":" << std::endl;
  std::shared_ptr<bTree<std::string, int> > pLkv = outer.get("outer1");
  pLkv->del("three");
  pLkv->del("three");
  pLkv->forEach([](const std::string &key, int &val){
    std::cout << "  Key: " << key << std::endl;
    std::cout << "  Val: " << val << std::endl;
  });
std::cout << "/****************** TEST 4 DONE *****************************/" << std::endl;

  //increment each val in second lkv
  pLkv = outer.get("outer2");
  pLkv->forEach([](const std::string &key, int &val){
    val++;
  });
  std::cout << "/****************** TEST 5 DONE *****************************/" << std::endl;

  //final iteration, should contain three in first set and
  //each val in second should be incremented
  std::cout << std::endl << std::endl << "After each item incremented:" << std::endl;
  outer.forEach([](const std::string &key, bTree<std::string, int> &val){
    std::cout << key << std::endl;
    val.forEach([](const std::string &key, int &val){
      std::cout << "  Key: " << key << std::endl;
      std::cout << "  Val: " << val << std::endl;
    });
  });
  std::cout << "/****************** TEST 6 DONE *****************************/" << std::endl;
  std::cout << "/****************** ALL DONE AMEN HALLELUJAH *****************************/" << std::endl;
#endif
  }
