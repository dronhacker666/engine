#!/usr/bin/env bash
. config
cd $1
. config

INCLUDE="${_INCLUDE} ${INCLUDE}"

function build
{
	OBJECTS=()
	HAVE_CHANGES=false
	local SOURCES=$1
	for SRC in $SOURCES; do
		OBJ_FILE=$OBJ_DIR/${SRC%.*}.o
		OBJECTS[${#OBJECTS[@]}]=$OBJ_FILE

		printf "Process %-50s: " $SRC
		if [ $OBJ_FILE -ot $SRC ]; then
			HAVE_CHANGES=true
			mkdir -p $OBJ_DIR/${SRC%/*}
			$CC -c $SRC $INCLUDE $PARAMS -o $OBJ_FILE
			if [ $? -ne 0 ]; then
				printf "FAILED\n"
				exit 1
			fi
			printf "OK\n"
		else
			printf "Skip\n"
		fi
	done
}

# Build Lib
if [ -n "$LIB_SOURCES" ]; then
	echo "Build Lib"
	build "${LIB_SOURCES}"
	if [ $HAVE_CHANGES=true ]; then
		mkdir -p $LIB_DIR
		ar rcs ${LIB_DIR}/lib${NAME}.a ${OBJECTS[@]}
	fi
fi

# Build Dynamic Lib
if [ -n "$DLIB_SOURCES" ]; then
	echo "Build Dynamic Lib"
	_PARAMS=$PARAMS
	PARAMS+=" -fPIC"
	build "${DLIB_SOURCES}"
	PARAMS=$_PARAMS
	if [ $HAVE_CHANGES=true ]; then
		mkdir -p $LIB_DIR
		mkdir -p $BIN_DIR
		$CC ${OBJECTS[@]} -o ${LIB_DIR}/lib${NAME}.dll $PARAMS $INCLUDE $LIB_DIRS $DLIB_LIBS -shared -Wl,--subsystem,windows
		cp ${LIB_DIR}/lib${NAME}.dll ${BIN_DIR}/lib${NAME}.dll
	fi 
fi

# Build exec
if [ -n "$EXE_SOURCES" ]; then
	echo "Build exec"
	build "${EXE_SOURCES}"
	if [ $HAVE_CHANGES=true ]; then
		mkdir -p $BIN_DIR
		$CC ${OBJECTS[@]} -o $BIN_DIR/$NAME $PARAMS $INCLUDE $LIB_DIRS $EXE_LIBS
	fi
fi