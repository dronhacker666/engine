NAME=escript
LIB_DIR=lib

CC=gcc
MAKE=mingw32-make
SOURCES=src/*.c
PARAMS= -s
LIBS=-L ${LIB_DIR} -l${NAME}

all: static
	${CC} -o run ${SOURCES} main.c ${PARAMS} ${LIBS}
	run.exe
	${MAKE} clean

run:
	${CC} -o run ${SOURCES} main.c ${PARAMS} ${LIBS}
	run.exe

lib:
	mkdir -p ${LIB_DIR}
	${CC} -c ${SOURCES}
	ar rc ${LIB_DIR}/lib${NAME}.a *.o
	ranlib ${LIB_DIR}/lib${NAME}.a
	${MAKE} clean

clean:
	rm -rf *.o
	rm -f run.exe