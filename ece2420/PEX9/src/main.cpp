

#include "Tree.hpp"
#include <string>
#include <iostream>

#if 1
static const char *numbers[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen",
    "twenty",
    "twenty one",
    "twenty two",
    "twenty three",
    "twenty four",
    "twenty five",
    "twenty six",
    "twenty seven",
    "twenty eight",
    "twenty nine",
    "thirty",
    "thirty one",
    "thirty two",
    "thirty three",
    "thirty four",
    "thirty five",
    "thirty six",
    "thirty seven",
    "thirty eight",
    "thirty nine",
    "forty",
    "forty one",
    "forty two",
    "forty three",
    "forty four",
    "forty five",
    "forty six",
    "forty seven",
    "forty eight",
    "forty nine",
    "fifty",
    "fifty one",
    "fifty two",
    "fifty three",
    "fifty four",
    "fifty five",
    "fifty six",
    "fifty seven",
    "fifty eight",
    "fifty nine",
    "sixty",
    "sixty one",
    "sixty two",
    "sixty three",
    "sixty four",
    "sixty five",
    "sixty six",
    "sixty seven",
    "sixty eight",
    "sixty nine",
    "seventy",
    "seventy one",
    "seventy two",
    "seventy three",
    "seventy four",
    "seventy five",
    "seventy six",
    "seventy seven",
    "seventy eight",
    "seventy nine",
    "eighty",
    "eighty one",
    "eighty two",
    "eighty three",
    "eighty four",
    "eighty five",
    "eighty six",
    "eighty seven",
    "eighty eight",
    "eighty nine",
    "ninety",
    "ninety one",
    "ninety two",
    "ninety three",
    "ninety four",
    "ninety five",
    "ninety six",
    "ninety seven",
    "ninety eight",
    "ninety nine",
};

#include <iostream>
#include <string>


template <typename KeyType, typename ValType>
class map : public Tree<KeyType, ValType>
{
};

int main()
{
  map<int, std::string> numeric;

  auto insertSet = [&numeric](std::function<int(int)> transform) {
    for (int i = 0; i < 20; ++i)
    {
      int n = transform(i);
      std::cout << "Insert " << n << std::endl;
      numeric.insert(n, numbers[n]);
      numeric.printTree();
      std::cout << std::endl;
    }
  };

  insertSet([](int i) { return 80 + i; });
  insertSet([](int i) { return 20 - i; });
  insertSet([](int i) { return 40 - i; });
  insertSet([](int i) { return 60 + i; });
  numeric.treeChecker();
  return 0;
}

#endif

#if 0

int main()
{

#if 1
  Tree<int, std::string> numeric;
  numeric.insert(4, "four");

  numeric.insert(2, "two");
  numeric.insert(6, "six");
  //numeric.printTree();
  numeric.insert(1, "one");
  numeric.insert(3, "three");

  numeric.insert(5, "five");
  numeric.insert(7, "seven");
  numeric.printTree();
  // for (int i = 1; i < 8; ++i)
  // {
  //   auto deli = numeric;
  //   deli.del(i);
  //   std::cout << "del" << i << ":";
  //   deli.forEach([](const int &key, std::string &val) {
  //     std::cout << val;
  //   });
  //   std::cout << std::endl;
  // }
#endif
#if 0
Tree<int, int> Tree;
  // Tree<std::string, int> lkv;
Tree.insert(2, 2);
Tree.insert(1, 1);
Tree.insert(3, 3);
Tree.del(3);
// Tree.del(3);

Tree.forEach([](const int &key, int &val){
  std::cout << "  Key: " << key << std::endl;
    std::cout << "  Val: " << val << std::endl;
});
#endif

#if 0

  Tree<std::string, Tree<std::string, int> > outer;
  Tree<std::string, int> lkv;
 
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
  outer.forEach([](const std::string &key, Tree<std::string, int> &val){
    std::cout << key << std::endl;
    val.forEach([](const std::string &key, int &val){
      std::cout << "  Key: " << key << std::endl;
      std::cout << "  Val: " << val << std::endl;
    });
  });
  std::cout << "/****************** TEST 3 DONE *****************************/" << std::endl;

  //make a copy of one LKV, delete an item, then iterate
  std::cout << std::endl << std::endl << "Deleted item \"three\":" << std::endl;
  std::shared_ptr<Tree<std::string, int> > pLkv = outer.get("outer1");
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
  outer.forEach([](const std::string &key, Tree<std::string, int> &val){
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
#endif
