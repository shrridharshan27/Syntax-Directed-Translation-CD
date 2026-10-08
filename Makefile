CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

all: build/sdt_suite

build/sdt_suite: src/sdt_suite.c
	mkdir -p build
	$(CC) $(CFLAGS) src/sdt_suite.c -o build/sdt_suite

run: all
	./build/sdt_suite

clean:
	rm -rf build *.exe
