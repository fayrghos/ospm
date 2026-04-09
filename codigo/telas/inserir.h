#pragma once

#include "../globais.h"
#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>
#include <allegro5/events.h>

void manusear_insercao(ALLEGRO_EVENT ev, Globais *globs);

void desenhar_insercao(
    Globais globs,
    ALLEGRO_BITMAP *danael,
    ALLEGRO_BITMAP *totem,
    ALLEGRO_FONT *fonte72,
    ALLEGRO_TIMER *timer
);