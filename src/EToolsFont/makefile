NAME=erender
LIB_DIR=lib

CC=gcc
MAKE=mingw32-make
SOURCES=src/*.c
PARAMS= -s
INCLUDE=-I include -I ../ELib/include
LIBS=-Llib -lfreetype

run:
	mkdir -p bin
	${CC} -o bin/run.exe ${INCLUDE} ${SOURCES} ${PARAMS} ${LIBS}
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