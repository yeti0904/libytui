CC   = clang++
src  = $(wildcard ./*.cc)
prog = $(subst ./,bin/,$(basename $(src)))
arg  = -g -Wall -pedantic -O3
lib  = /usr/lib/libytui.a

all: $(prog)

$(prog): bin/% : ./%.cc
	mkdir -p bin
	$(CC) $(arg) -o $@ $< $(lib)

clean:
	rm -r bin
