#pragma once

#include <allegro5/allegro_font.h>

/*
 * Pequena abstração para carregar fontes com segurança.
 */
ALLEGRO_FONT *carregar_fonte(char *diretorio, int tamanho);

/*
 * Pequena abstração para carregar imagens com segurança.
 */
ALLEGRO_BITMAP *carregar_bitmap(char *diretorio);