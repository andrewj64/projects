#include "ListKeyVal.hpp"
#include <string>
#include <iostream>

int main()
{
  ListKeyVal<std::string, ListKeyVal<std::string, int>> outer;
  ListKeyVal<std::string, int> inner;

  inner.insert("one",   1);
  inner.insert("two",   2);
  inner.insert("three", 3);
  std::cout << "insert 1, 2, 3" << std::endl;
  inner.del("two");
  std::cout << "delete 2" << std::endl;
  *(inner.get("three")) = 4;
  inner.forEach([](const std::string &key, int &val){
    std::cout << key << val;
  });

#if 0
  //populate an LKV  
  lkv.insert("one", 1);
  lkv.insert("three", 3);
  lkv.insert("four", 4);
  lkv.insert("two", 2);

  std::cout << "/****************** TEST 1 DONE *****************************/" << std::endl;

  //put two copies map into outer
  outer.insert("outer1", lkv);
  outer.insert("outer2", lkv);
  std::cout << "/****************** TEST 2 DONE *****************************/" << std::endl;

  //iterate over outer then inner
  std::cout << std::endl << std::endl << "Full iteration:" << std::endl;
  outer.forEach([](const std::string &key, ListKeyVal<std::string, int> &val){
    std::cout << key << std::endl;
    val.forEach([](const std::string &key, int &val){
      std::cout << "  Key: " << key << std::endl;
      std::cout << "  Val: " << val << std::endl;
    });
  });
  std::cout << "/****************** TEST 3 DONE *****************************/" << std::endl;

  //make a copy of one LKV, delete an item, then iterate
  std::cout << std::endl << std::endl << "Deleted item \"three\":" << std::endl;
  std::shared_ptr<ListKeyVal<std::string, int> > pLkv = outer.get("outer1");
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
  outer.forEach([](const std::string &key, ListKeyVal<std::string, int> &val){
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
