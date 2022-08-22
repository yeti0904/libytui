# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

APP = ./bin/libytui.a

# compiler related
CXX = clang++
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

# rules
compile: ./bin ${OBJ} ${SRC}
	ar rcs ${APP} bin/*.o

./bin:
	mkdir -p bin

bin/%.o: src/%.cc ${DEPS}
	${CXX} -c $< ${CXXFLAGS} -o $@

clean:
	rm bin/*.o $(APP)

install:
	cp ${APP} /usr/lib/
	mkdir -p /usr/include/libytui
	cp src/*.hh /usr/include/libytui/

all:
	@echo compile
	@echo install
	@echo clean
