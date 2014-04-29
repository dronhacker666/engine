CC=gcc
MAKE=mingw32-make
SOURCES=*.c
LIBS=-L lib -llua52 -lopengl32
PARAMS= -s
OUT=bin/run

all: EScript_static ERender_static ECore_static

ECore:
	${CC} -o ${OUT} ${SOURCES} ${PARAMS} ${LIBS}
	${OUT}

EScript_static:
	cd src/EScript && ${MAKE} static
	cp src/EScript/lib/* lib

ERender_static:
	cd src/ERender && ${MAKE} static
	cp src/ERender/lib/* lib
