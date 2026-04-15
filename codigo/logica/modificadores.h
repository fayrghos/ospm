#pragma once

#include "../globais.h"
#include <allegro5/events.h>

/*
 * Detecta e gerencia quais modificadores o usuário está apertando.
 */
void manusear_modificadores(ALLEGRO_EVENT ev, Modificadores *mods);
