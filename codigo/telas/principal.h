#pragma once

#include "../globais.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/events.h>

/*
 * Redesenho da tela principal.
 */
void desenhar_principal(
    ALLEGRO_FONT *fonte_p, ALLEGRO_FONT *fonte_m, Globais globs
);

/*
 * Lógica da tela principal.
 */
void manusear_principal(ALLEGRO_EVENT ev, Globais *globs);
