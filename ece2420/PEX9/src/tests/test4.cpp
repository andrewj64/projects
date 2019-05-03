#include <iostream>
#include "include.hpp"

int main()
{
#include "instantiate.hpp"

  //populate
  inner.insert("one", 1);
  inner.insert("two", 2);
  outer.insert("outer1", inner);
  outer.insert("outer2", inner);

  inner.insert("one", 3);
  inner.insert("two", 4);

  outer.get("outer1")->insert("one", 5);
  outer.get("outer2")->insert("two", 6);

  outer.forEach([](const std::string &key, KeyVal<std::string, int> &val){
    std::cout << key;
    val.forEach([](const std::string &key, int &val){
      std::cout << key << val;
    });
  });
}
