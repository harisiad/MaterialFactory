WFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror

all:
	g++ $(WFLAGS) main.cpp -g -o main
run:
	./main
clean:
	rm a.out
