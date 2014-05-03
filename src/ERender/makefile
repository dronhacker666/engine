NAME=erender
LIB_DIR=lib

CC=gcc
MAKE=mingw32-make
SOURCES=src/imageDecoder/*.c src/*.c
PARAMS= -s
LIBS=-lOpenGL32 -lGdi32 -L../ELib/lib -lelib

run:
	mkdir -p bin
	${CC} -o bin/run.exe ${SOURCES} main.c ${PARAMS} ${LIBS}
	cd bin && ./run.exe

build_lib:
	mkdir -p ${LIB_DIR}
	${CC} -c ${SOURCES}
	ar rc ${LIB_DIR}/lib${NAME}.a *.o
	ranlib ${LIB_DIR}/lib${NAME}.a
	${MAKE} clean

clean:
	rm -rf *.o
	rm -f run.exe