#pragma once

#include "../globais.h"
#include "fila.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include <stdlib.h>

void desenhar_linha_de_execucao(Globais *os, ALLEGRO_FONT *fonte);

void round_robin(Globais *os);
void fist_in(Globais *os);
void heap_struct(Globais *os);
void smallest(Globais *os);

void carregar_fila(Globais *os);