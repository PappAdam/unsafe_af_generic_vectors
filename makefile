FILES  = src/main.c src/vector/vector.c


all: $(FILES)
	clang $(FILES) -o main
	./main

