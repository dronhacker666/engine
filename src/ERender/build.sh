#!/usr/bin/env bash
. config

OBJECTS=()
for SRC in $SOURCES; do
	OBJ_FILE=$OBJ_DIR/${SRC%.*}.o
	OBJECTS[${#OBJECTS[@]}]=$OBJ_FILE

	printf "Process %-50s: " $SRC
	if [ $OBJ_FILE -ot $SRC ]; then
		mkdir -p $OBJ_DIR/${SRC%/*}
		$CC -c $SRC $INCLUDE $PARAMS -o $OBJ_FILE
		printf "OK\n"
	else
		printf "Skip\n"
	fi
done

mkdir -p $BIN_DIR
$CC ${OBJECTS[@]} -o $BIN_DIR/$EXE_NAME $PARAMS $LIBS