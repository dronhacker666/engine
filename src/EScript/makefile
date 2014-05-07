NAME=escript
LIB_DIR=lib

CC=gcc
MAKE=mingw32-make
SOURCES=src/*.c
PARAMS= -s
INCLUDE=-I ../ELib/include -I src
LIBS=-L ../ELib/lib -lelib

run:
	${CC} -o run ${SOURCES} main.c ${INCLUDE} ${PARAMS} ${LIBS}
	run.exe

lib:
	mkdir -p ${LIB_DIR}
	${CC} -c ${SOURCES} ${INCLUDE}
	ar rc ${LIB_DIR}/lib${NAME}.a *.o
	ranlib ${LIB_DIR}/lib${NAME}.a
	${MAKE} clean

clean:
	rm -rf *.o
	rm -f run.exe