#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>

ALLEGRO_FONT *carregar_fonte(char *diretorio, int tamanho) {
    ALLEGRO_FONT *saida = al_load_font(diretorio, tamanho, 0);

    if (!saida) {
        fprintf(stderr, "A fonte '%s' não foi encontrada!\n", diretorio);
        exit(1);
    }

    return saida;
}

ALLEGRO_BITMAP *carregar_bitmap(char *diretorio) {
    ALLEGRO_BITMAP *saida = al_load_bitmap(diretorio);

    if (!saida) {
        fprintf(stderr, "A imagem '%s' não foi encontrada!\n", diretorio);
        exit(1);
    }

    return saida;
}

void rodar_inteiro(int min, int max, int *atual, int fator) {
    if (*atual + fator < min) {
        *atual = min;
        return;
    }

    if (*atual + fator > max) {
        *atual = max;
        return;
    }

    *atual += fator;
}