test: generator.cpp main.cpp main.py
	make generator
	make main
	./test.sh

generator: generator.cpp
	clang++ generator.cpp -o generator -std=c++17 -O2

main: main.cpp
	clang++ main.cpp ../../src/support/u99.cpp -o main -std=c++17

clean:
	rm -f input answer output generator main
