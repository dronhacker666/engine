CC=gcc
MAKE=mingw32-make

INCLUDE=-I include -I src
SOURCES=src/*.c

LIB_DIR=lib
NAME=elib

run:
	mkdir -p bin
	${CC} tests/*.c ${SOURCES} ${INCLUDE} -o bin/run.exe -s
	bin/run.exe

build_lib:
	mkdir -p lib
	${CC} ${SOURCES} ${INCLUDE} -o ${LIB_DIR}/lib${NAME}.dll -shared -s
	${CC} -c ${SOURCES} ${INCLUDE}
	ar rc ${LIB_DIR}/lib${NAME}.a *.o
	ranlib ${LIB_DIR}/lib${NAME}.a
	rm -rf *.o