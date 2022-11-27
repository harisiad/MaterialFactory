WFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror

all:
	g++ $(WFLAGS) main.cpp factory.cpp -g -o main
	g++ $(WFLAGS) -I test/doctest/doctest ./test/factoryUnitTest.cpp factory.cpp -g -o testRun
runTest:
	./testRun
run:
	./testRun
	./main
clean:
	rm a.out
