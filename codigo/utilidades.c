#include <allegro5/allegro_font.h>
#include <stdio.h>

/*
 * Pequena abstração para carregar fontes com segurança.
 */
ALLEGRO_FONT *carregar_fonte(char *diretorio, int tamanho) {
    ALLEGRO_FONT *saida = al_load_font(diretorio, tamanho, 0);

    if (!saida) {
        fprintf(stderr, "A fonte '%s' não foi encontrada!\n", diretorio);
        return al_create_builtin_font();
    }

    return saida;
}

/*
 * Pequena abstração para carregar imagens com segurança.
 */
ALLEGRO_BITMAP *carregar_bitmap(char *diretorio) {
    ALLEGRO_BITMAP *saida = al_load_bitmap(diretorio);

    if (!saida) {
        fprintf(stderr, "A imagem '%s' não foi encontrada!\n", diretorio);
        return NULL;
    }

    return saida;
}