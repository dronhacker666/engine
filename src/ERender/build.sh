#!/usr/bin/env bash
. config

OBJECTS=()
for SRC in $SOURCES; do
	OBJ_FILE=$OBJ_DIR/${SRC%.*}.o
	OBJECTS[${#OBJECTS[@]}]=$OBJ_FILE

	if [ $OBJ_FILE -ot $SRC ]; then
		mkdir -p $OBJ_DIR/${SRC%/*}
		$CC -c $SRC $INCLUDE -o $OBJ_FILE
	fi
done

mkdir -p $BIN_DIR
$CC ${OBJECTS[@]} -o $BIN_DIR/$EXE_NAME $PARAMS $LIBS