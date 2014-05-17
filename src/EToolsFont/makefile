CC=gcc
MAKE=mingw32-make

NAME=font
LIB_DIR=lib

run:
	mkdir -p bin

	#font converter
	#${CC} -s -o bin/fontconv.exe -I include src/fontconv.c -Llib -lfreetype
	#cd bin && ./fontconv.exe

	${CC} -o bin/run.exe -I include -I ../ELib/include src/libfont.c main.c -s -L ../ELib/lib -lelib
	cd bin && ./run.exe

build_lib:
	mkdir -p ${LIB_DIR}
	${CC} -c src/libfont.c -I include -I ../ELib/include
	ar rc ${LIB_DIR}/lib${NAME}.a *.o
	ranlib ${LIB_DIR}/lib${NAME}.a
	${MAKE} clean

clean:
	rm -rf *.o
	rm -f run.exe