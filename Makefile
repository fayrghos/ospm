EXEC := bin/ospm
ARGS :=

CODIGOS := $(shell find . -name "*.c")
FLAGS :=

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


# Roda casualmente o programa
normal: compilar
	./${EXEC} ${ARGS}


# Executa o programa no modo rápido
rapido r: ARGS += --rapido
rapido r: compilar
	./${EXEC} ${ARGS}


# Chama o GDB para fazer debug
debug d: FLAGS += -g
debug d: compilar
	gdb ${EXEC} -q


# Apenas compila o binário
compilar:
	@mkdir -p bin
	gcc ${FLAGS} ${CODIGOS} ${BIBLIOS} -o ${EXEC}


.PHONY: normal rapido r debug d compilar
