CC := gcc

CCFLAGS := -Iinclude -Wall -Wextra -std=c99 -O3 -march=native

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/%.o, $(SOURCES))

TARGET := bin/hashmap

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CC) -o $@ $^

bin:
	mkdir -p $@

build/%.o: src/%.c | build
	$(CC) -c -o $@ $< $(CCFLAGS)

build:
	mkdir -p $@

clean:
	$(RM) -r build bin

PHONY: all clean


