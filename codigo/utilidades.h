#pragma once

#include <allegro5/allegro_font.h>

/*
 * Não permite que o programa continue rodando sem a fonte.
 */
ALLEGRO_FONT *carregar_fonte(char *diretorio, int tamanho);

/*
 * Não permite que o programa continue rodando sem o bitmap.
 */
ALLEGRO_BITMAP *carregar_bitmap(char *diretorio);

/*
 * Altera o valor de um inteiro com base no 'fator'.
 * Não pode virar menor que 'min' nem maior que 'max'.
 */
void rodar_inteiro(int min, int max, int *atual, int fator);

/*
 * Desenha uma caixa de erro na tela se 'titulo' não for uma string vazia.
 */
void desenhar_erros(char *titulo, ALLEGRO_FONT *fonte);

/*
 * Desenha um botão com um determinado título.
 */
void desenhar_botao(
    float x,
    float y,
    char *titulo,
    char *escrita,
    bool selecionado,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
);
