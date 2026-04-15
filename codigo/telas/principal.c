#include "../globais.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>

// Horizontais
#define LHM ALTURA / 2
#define LHI ALTURA / 4 + LHM

void desenhar_principal(ALLEGRO_FONT *fonte) {
    static const short bd = 30;
    static const float mapa_l = LHM - (bd * 2);

    // --------------------------------------------------
    // Tabela
    // --------------------------------------------------
    al_draw_filled_rectangle(
        bd, bd, LARGURA / 2 - bd, ALTURA / 2 - bd, al_map_rgb(100, 100, 100)
    );

    // --------------------------------------------------
    // Gráfico
    // --------------------------------------------------

    static const short espaco = 75;

    al_draw_filled_rectangle(
        bd, LHM + bd, LARGURA - bd, ALTURA - bd, al_map_rgb(15, 15, 15)
    );

    // Linha central
    // al_draw_filled_rectangle(
    //     bd * 3, LHI - 3, LARGURA - bd * 3, LHI + 3, al_map_rgb(100, 100, 100)
    // );

    // Linha superior
    al_draw_filled_rectangle(
        bd * 3,
        LHI - espaco - 3,
        LARGURA - bd * 3,
        LHI - espaco + 3,
        al_map_rgb(100, 100, 100)
    );

    // Linha inferior
    al_draw_filled_rectangle(
        bd * 3,
        LHI + espaco - 3,
        LARGURA - bd * 3,
        LHI + espaco + 3,
        al_map_rgb(100, 100, 100)
    );

    // CPU
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) - 125,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de CPU"
    );

    // IO
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) + 35,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de IO"
    );
}
