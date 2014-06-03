MAKE=mingw32-make

# Engine section
ENGINE_DIR=src/ERender
engine_run: engine_build
	bash run.sh ${ENGINE_DIR}
engine_build:
	bash build.sh ${ENGINE_DIR}
engine_clean:
	bash clean.sh ${ENGINE_DIR}

# Editor section
EDITOR_DIR=src/EEditor
editor_run: editor_build
	cp ${ENGINE_DIR}/lib/librender.dll ${EDITOR_DIR}/bin/librender.dll
	bash run.sh ${EDITOR_DIR}
editor_build: engine_build
	bash build.sh ${EDITOR_DIR}
editor_clean:
	bash clean.sh ${EDITOR_DIR}