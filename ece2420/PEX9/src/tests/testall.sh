#!/bin/bash

if [[ $# -ne 1 ]] ; then
 echo "Usage: testall <NameOfClass>"
 exit 1
fi

#make include files
echo "#include \"../$1.hpp\"" > include.hpp
echo "$1<std::string, $1<std::string, int> > outer;"                                   > instantiate.hpp
echo "$1<std::string, int> inner;"                                                    >> instantiate.hpp
echo "std::shared_ptr<KeyVal<std::string, int> > pKeyVal(new $1<std::string, int>); " >> instantiate.hpp
echo "$1<int, std::string> numeric;" >> instantiate.hpp

mkdir -p bin actual

#compile and execute third test (copy construct and assign)
g++ -g -std=c++11 test3.cpp -o bin/test3 2>/dev/null
if [[ $? -ne 0 ]] ; then
  echo "Failed copy/assign compilation test"
else
  bin/test3 | grep success > /dev/null && echo "Passed cp ctor and assign test" || echo "Failed cp ctor and assign test"
fi

#compile and execute fourth test (deep copy)
g++ -g -std=c++11 test4.cpp -o bin/test4 
if [[ $? -ne 0 ]] ; then
  echo "Failed deep copy compilation test"
else
  bin/test4 | grep outer1one5two2outer2one1two6 > /dev/null && echo "Passed deep copy test" || echo "Failed deep copy test"
fi

#compile and execute fifth test (modify after get)
g++ -g -std=c++11 test5.cpp -o bin/test5 
if [[ $? -ne 0 ]] ; then
  echo "Failed get/modify compilation test"
else
  bin/test5 | grep 3 > /dev/null && echo "Passed get/modify test" || echo "Failed get/modify test"
fi

#compile and execute sixth test (modify in foreach)
#doesn't check ordering
g++ -g -std=c++11 test6.cpp -o bin/test6 
if [[ $? -ne 0 ]] ; then
  echo "Failed modify in foreach compilation test"
else
  bin/test6 | grep 2 > /dev/null
  if [[ $? -eq 0 ]] ; then
    bin/test6 | grep 3 > /dev/null
    if [[ $? -eq 0 ]] ; then
      bin/test6 | grep 4 > /dev/null
      if [[ $? -eq 0 ]] ; then
        echo "Passed foreach modify test"
      else
        echo "Failed foreach modify test"
      fi
    else
      echo "Failed foreach modify test"
    fi
  else
    echo "Failed foreach modify test"
  fi
fi

#compile and execute seventh test (iterate in order)
g++ -g -std=c++11 test7.cpp -o bin/test7 
if [[ $? -ne 0 ]] ; then
  echo "Failed in order iteration compilation test"
else
  bin/test7 | grep 132 > /dev/null && echo "Passed in order iteration test" || echo "Failed in order itration test"
fi

#compile and execute h test (insert at head)
#doesn't check ordering
g++ -g -std=c++11 test8.cpp -o bin/test8 
if [[ $? -ne 0 ]] ; then
  echo "Failed insert at head compilation test"
else
  bin/test8 | grep 1 > /dev/null
  if [[ $? -eq 0 ]] ; then
    bin/test8 | grep 2 > /dev/null
    if [[ $? -eq 0 ]] ; then
      bin/test8 | grep 3 > /dev/null
      if [[ $? -eq 0 ]] ; then
        echo "Passed insert at head test"
      else
        echo "Failed insert at head test"
      fi
    else
      echo "Failed insert at head test"
    fi
  else
    echo "Failed insert at head test"
  fi
fi

#compile and execute ninth test (get/del non-key)
g++ -g -std=c++11 test9.cpp -o bin/test9 
if [[ $? -ne 0 ]] ; then
  echo "Failed non existing key compilation test"
else
  bin/test9 | grep success > /dev/null && echo "Passed non-key test" || echo "Failed non-key test"
fi

#compile and execute tenth test (tree insert)
g++ -g -std=c++11 test10.cpp -o bin/test10
if [[ $? -ne 0 ]] ; then
  echo "Failed tree insert compilation test"
else
  bin/test10 | grep "onetwothreefourfivesixseven" > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed tree insert test"
  else
    echo "Failed tree insert test"
  fi
fi

#compile and execute eleventh test (red uncle recolor)
g++ -g -std=c++11 test11.cpp -o bin/test11
if [[ $? -ne 0 ]] ; then
  echo "Failed red uncle recolor compilation test"
else
  bin/test11 > actual/test11.txt
  diff actual/test11.txt expected/test11.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed red uncle recolor test"
  else
    echo "Failed red uncle recolor test"
  fi
fi

#compile and execute twelfth test (basic rotations root change)
g++ -g -std=c++11 test12.cpp -o bin/test12
if [[ $? -ne 0 ]] ; then
  echo "Failed basic rotations root change compilation test"
else
  bin/test12 > actual/test12.txt
  diff actual/test12.txt expected/test12.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed basic rotations root change test"
  else
    echo "Failed basic rotations root change test"
  fi
fi

#compile and execute thirteenth test (recurse 1 rotations)
g++ -g -std=c++11 test13.cpp -o bin/test13
if [[ $? -ne 0 ]] ; then
  echo "Failed recurse 1 rotations compilation test"
else
  bin/test13 > actual/test13.txt
  diff actual/test13.txt expected/test13.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed recurse 1 rotations test"
  else
    echo "Failed recurse 1 rotations test"
  fi
fi

#compile and execute fourteenth test (big data rotations)
g++ -g -std=c++11 test14.cpp -o bin/test14
if [[ $? -ne 0 ]] ; then
  echo "Failed big data rotations compilation test"
else
  bin/test14 > actual/test14.txt
  diff actual/test14.txt expected/test14.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed big data rotations test"
  else
    echo "Failed big data rotations test"
  fi
fi

#compile and execute rbdel test
g++ -g -std=c++11 rbdel.cpp -o bin/rbdel
if [[ $? -ne 0 ]] ; then
  echo "Failed rbdel compilation test"
else
  bin/rbdel 1 > actual/rbdel1.txt
  diff actual/rbdel1.txt expected/rbdel1.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed rbdel basic test"
  else
    echo "Failed rbdel basic test"
  fi
  bin/rbdel 2 > actual/rbdel2.txt
  diff actual/rbdel2.txt expected/rbdel2.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed rbdel black black test"
  else
    echo "Failed rbdel black black test"
  fi
  bin/rbdel 3 > actual/rbdel3.txt
  diff actual/rbdel3.txt expected/rbdel3.txt > /dev/null
  if [[ $? -eq 0 ]] ; then
    echo "Passed rbdel recurse red test"
  else
    echo "Failed rbdel recurse red test"
  fi
fi

#mem leak test
#test1 should be a sufficient test for mem leaks
valgrind bin/test3 2>&1 | grep "no leaks are possible" > /dev/null && echo "Passed leak test" || echo "Failed leak test"
