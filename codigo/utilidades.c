#include "globais.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
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

void desenhar_botao(
    float x,
    float y,
    char *titulo,
    char *escrita,
    bool selecionado,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
) {
    al_draw_text(
        fonte_p,
        al_map_rgb(255, 255, 255),
        x - 300,
        y - 100,
        ALLEGRO_ALIGN_LEFT,
        titulo
    );

    if (selecionado) {
        al_draw_filled_rounded_rectangle(
            x - 303, y - 53, x + 303, y + 53, 20, 20, al_map_rgb(222, 221, 218)
        );
    }

    al_draw_filled_rounded_rectangle(
        x - 300, y - 50, x + 300, y + 50, 20, 20, al_map_rgb(52, 52, 54)
    );

    if (selecionado && al_get_timer_count(timer) % 20 >= 10 &&
        escrita[0] == '\0') {
        al_draw_text(
            fonte_g,
            al_map_rgb(255, 255, 255),
            x,
            y - 40,
            ALLEGRO_ALIGN_CENTER,
            "_"
        );
    }

    al_draw_text(
        fonte_g,
        al_map_rgb(255, 255, 255),
        x,
        y - 40,
        ALLEGRO_ALIGN_CENTER,
        escrita
    );
}

void desenhar_texto_cen(int x, int y, ALLEGRO_FONT *fonte, char *texto) {
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        x,
        y - (al_get_font_line_height(fonte) / 2.0),
        ALLEGRO_ALIGN_CENTER,
        texto
    );
}
