test: generator.cpp main.cpp main.py
	make generator
	make main
	./test.sh

generator: generator.cpp
	clang++ generator.cpp -o generator -std=c++17 -O2

main: main.cpp
	clang++ main.cpp ../../src/support/u99.cpp ../../src/support/i99.cpp -o main -std=c++17 -fsanitize=address -fsanitize=undefined

clean:
	rm -f input answer output generator main
