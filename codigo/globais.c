#include "globais.h"
#include <allegro5/color.h>
#include <stdio.h>

ALLEGRO_COLOR traduzir_cor_proc(ECorProcesso cor) {
    cor = cor % MAX_CORES;

    switch (cor) {
    case C_VERMELHO:
        return al_map_rgb(192, 28, 40);

    case C_VERDE:
        return al_map_rgb(51, 209, 122);

    case C_AZUL:
        return al_map_rgb(28, 113, 216);

    case C_CIANO:
        return al_map_rgb(153, 193, 241);

    case C_MAGENTA:
        return al_map_rgb(192, 97, 203);

    case C_AMARELO:
        return al_map_rgb(248, 228, 92);

    case C_CINZA:
        return al_map_rgb(94, 92, 100);

    case C_LARANJA:
        return al_map_rgb(255, 163, 72);

    case C_MARROM:
        return al_map_rgb(152, 106, 68);

    case C_PRETO:
        return al_map_rgb(0, 0, 0);

    default:
        fprintf(stderr, "A tradução de cores falhou em encontrar '%d'!\n", cor);
        exit(1);
    }
}