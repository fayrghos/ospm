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
    case 5: // Amarelo
        return al_map_rgb(247, 210, 62);
    case 6: // Roxo
        return al_map_rgb(140, 82, 255);
    case 7: // Azul
        return al_map_rgb(31, 72, 255);
    case 8: // Cinza
        return al_map_rgb(138, 138, 138);
    case 9: // Marrom
        return al_map_rgb(174, 84, 28);
    default:
        fprintf(stderr, "A tradução de cores falhou em encontrar '%d'!\n", cor);
        exit(1);
    }
}
