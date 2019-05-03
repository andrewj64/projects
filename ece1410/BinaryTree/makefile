LogTable.exe: main.o btree.o node.o
				g++ -o LogTable.exe main.o btree.o node.o

main.o: main.cpp node.h btree.h
				g++ -c  main.cpp
				
btree.o: btree.cpp btree.h
			g++ -c btree.cpp
			
node.o: node.cpp node.h
			g++ -c node.cpp 