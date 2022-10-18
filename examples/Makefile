ifeq ($(platform), windows)
CXX  = x86_64-w64-mingw32-g++
else
CXX  = clang++
endif
src  = $(wildcard ./*.cc)
prog = $(subst ./,bin/,$(basename $(src)))
arg  = -g -Wall -pedantic -O3
lib  = /usr/lib/libytui.a

ifeq ($(platform), windows)
arg += -I../ -static -static-libgcc -static-libstdc++
endif

all: $(prog)

$(prog): bin/% : ./%.cc
	mkdir -p bin
	$(CXX) $(arg) -o $@ $< $(lib)

clean:
	rm -r bin
