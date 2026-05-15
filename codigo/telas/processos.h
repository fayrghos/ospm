#pragma once

#include "../globais.h"
#include "../logica/linhaOS.h"
#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

/*
 * Lógica da tela de definição de processos.
 */
void manusear_processos(ALLEGRO_EVENT ev, Globais *globs);

/*
 * Redesenho da tela de definição de processos.
 */
void desenhar_processos(
    Globais globs,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
);
