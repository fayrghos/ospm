#pragma once

#include "../globais.h"
#include "../logica/linhaOS.h"
#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

void manusear_definicao(ALLEGRO_EVENT ev, Globais *globs, Ospm *ospm);

void desenhar_definicao(
    Globais globs,
    Ospm ospm,
    ALLEGRO_BITMAP *danael,
    ALLEGRO_BITMAP *totem,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
);