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