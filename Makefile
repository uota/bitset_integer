.PHONY: all
all: test factorial1000 pi root2

test: test.cpp
	g++ -std=c++11 -O0 -g3 -Wall -o test test.cpp

factorial1000: factorial1000.cpp
	g++ -std=c++11 -O2 -Wall -o factorial1000 factorial1000.cpp

pi: pi.cpp
	g++ -std=c++11 -O2 -Wall -o pi pi.cpp

root2: root2.cpp
	g++ -std=c++11 -O2 -Wall -o root2 root2.cpp

clean:
	rm test factorial1000 pi root2
