EXEC := bin/ospm
ARGS :=

CODIGOS := $(shell find . -name "*.c")
FLAGS :=

ALLEGRO := $(shell pkg-config --libs \
    allegro-5 \
    allegro_ttf-5 \
    allegro_font-5 \
    allegro_image-5 \
    allegro_audio-5 \
    allegro_video-5 \
    allegro_primitives-5)


# Roda casualmente o programa
normal: compilar
	./$(EXEC) $(ARGS)


# Executa o programa no modo rápido
rapido r: ARGS += --rapido
rapido r: compilar
	./$(EXEC) $(ARGS)


# Chama o GDB para fazer debug
debug d: FLAGS += -g
debug d: compilar
	gdb $(EXEC) -q


# Apenas compila o binário
compilar:
	@mkdir -p bin
	gcc $(FLAGS) $(CODIGOS) $(ALLEGRO) -o $(EXEC)


.PHONY: normal rapido r debug d compilar
