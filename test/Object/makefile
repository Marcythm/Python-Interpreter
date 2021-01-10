test: generator.cpp main.cpp main.py
	make generator
	make main
	./test.sh

generator: generator.cpp
	clang++ generator.cpp -o generator -std=c++2a -O2

# *.o: *.cpp
# 	clang++ -c $< -o $@ -std=c++2a -mcmodel=medany

# main: main.cpp
# 	clang++ main.cpp ../../src/support/*.cpp -o main -std=c++2a -fsanitize=address -fsanitize=undefined

u99.o: ../../src/support/u99.cpp
	clang++ -c ../../src/support/u99.cpp -o u99.o -std=c++2a -mcmodel=medany
i99.o: ../../src/support/i99.cpp
	clang++ -c ../../src/support/i99.cpp -o i99.o -std=c++2a -mcmodel=medany
Object.o: ../../src/support/Object.cpp
	clang++ -c ../../src/support/Object.cpp -o Object.o -std=c++2a -mcmodel=medany
main.o: main.cpp
	clang++ -c main.cpp -o main.o -std=c++2a -mcmodel=medany

main: u99.o i99.o Object.o main.o
	clang++ u99.o i99.o Object.o main.o -o main -Wl,-no_pie


clean:
	rm -f input answer output generator main *.o
