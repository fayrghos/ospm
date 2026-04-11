#include "globais.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
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

void desenhar_erros(char *titulo, ALLEGRO_FONT *fonte) {
    if (titulo[0] != '\0') {
        al_draw_filled_rounded_rectangle(
            297,
            ALTURA - 83,
            LARGURA - 297,
            ALTURA - 17,
            15,
            15,
            al_map_rgb(237, 51, 59)
        );

        al_draw_filled_rounded_rectangle(
            300,
            ALTURA - 80,
            LARGURA - 300,
            ALTURA - 20,
            15,
            15,
            al_map_rgb(52, 52, 54)
        );
    }

    al_draw_text(
        fonte,
        al_map_rgb(246, 97, 81),
        LARGURA / 2,
        ALTURA - 68,
        ALLEGRO_ALIGN_CENTER,
        titulo
    );
}