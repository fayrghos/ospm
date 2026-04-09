CODIGO := $(shell find . -name "*.c")

EXEC := viewer.out
EXEC_DIR := bin/
EXEC_CAMINHO := ${EXEC_DIR}${EXEC}

BIBLIOS := \
	-lm \
	-lallegro \
	-lallegro_main \
	-lallegro_audio \
	-lallegro_dialog \
	-lallegro_ttf \
	-lallegro_image \
	-lallegro_color \
	-lallegro_memfile \
	-lallegro_acodec \
	-lallegro_primitives \
	-lallegro_font \
	-lallegro_video


rodar: compilar
	@./${EXEC_CAMINHO}


debug: compilar
	gdb ${EXEC_CAMINHO} -q


compilar:
	@mkdir -p ${EXEC_DIR}
	gcc ${CODIGO} ${BIBLIOS} -g -o ${EXEC_CAMINHO}


limpar:
	@rm -rf ${EXEC_DIR}