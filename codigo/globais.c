#include "globais.h"
#include <allegro5/color.h>
#include <stdio.h>

ALLEGRO_COLOR traduzir_cor(int cor) {
    cor %= MAX_CORES;

    switch (cor) {
    case 0: // Vermelho
        return al_map_rgb(255, 87, 87);
    case 1: // Ciano
        return al_map_rgb(56, 182, 255);
    case 2: // Verde
        return al_map_rgb(0, 191, 99);
    case 3: // Magenta
        return al_map_rgb(203, 108, 230);
    case 4: // Laranja
        return al_map_rgb(255, 145, 77);
    default:
        fprintf(stderr, "A tradução de cores falhou em encontrar '%d'!\n", cor);
        exit(1);
    }
}
