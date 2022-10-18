# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

APP = ./bin/libytui.a

# compiler related
ifeq (${platform}, windows)
CXX = x86_64-w64-mingw32-g++
AR  = x86_64-w64-mingw32-ar
else
CXX = clang++
AR  = ar
endif
CXXVER = c++17
CXXFLAGS = \
	-O3 \
	-std=${CXXVER} \
	-Wall \
	-Wextra \
	-pedantic \
	-g \
	-Wno-deprecated-declarations

CXXLIBS = 

ifeq (${platform}, windows)
	CXXFLAGS += -static -static-libgcc -static-libstdc++
endif

# rules
compile: ./bin ${OBJ} ${SRC}
	${AR} rcs ${APP} bin/*.o

./bin:
	mkdir -p bin

bin/%.o: src/%.cc ${DEPS}
	${CXX} -c $< ${CXXFLAGS} -o $@

clean:
	rm bin/*.o $(APP)

install:
	cp ${APP} /usr/lib/
	mkdir -p libytui
	cp src/*.hh libytui/
	cp -r libytui /usr/include/

all:
	@echo compile
	@echo install
	@echo clean
