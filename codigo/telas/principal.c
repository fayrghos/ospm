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

    // --------------------------------------------------
    // Tabela
    // --------------------------------------------------

    al_draw_filled_rectangle(
        bd, bd, LARGURA / 2 - bd, ALTURA / 2 - bd, al_map_rgb(52, 52, 54)
    );

    // Barra superior
    al_draw_filled_rectangle(
        bd + 25,
        bd + 16,
        LARGURA / 2 - bd - 25,
        bd + 134,
        al_map_rgb(84, 84, 84)
    );

    // Barrinhas
    for (int i = 0; i < 3; i++) {
        al_draw_filled_rectangle(
            bd + 25,
            bd + 139 + (i * 58),
            LARGURA / 2 - bd - 25,
            bd + 192 + (i * 58),
            al_map_rgb(84, 84, 84)
        );
    }

    // Paginador
    al_draw_filled_rectangle(
        bd + 48, bd + 41, bd + 166, bd + 109, al_map_rgb(255, 255, 255)
    );
    al_draw_filled_rectangle(
        bd + 51, bd + 44, bd + 163, bd + 106, al_map_rgb(15, 15, 15)
    );

    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        bd + 107,
        bd + 65,
        ALLEGRO_ALIGN_CENTER,
        "Pág. 1"
    );

    // Processos
    for (int i = 0; i < 5; i++) {
        al_draw_filled_circle(
            bd + 230 + (i * 79), bd + 74, 30, al_map_rgb(255, 255, 255)
        );
        al_draw_filled_circle(
            bd + 230 + (i * 79), bd + 74, 27, traduzir_cor_proc(i)
        );
    }

    // IDs de Processo
    for (int i = 0; i < 5; i++) {
        al_draw_textf(
            fonte,
            al_map_rgb(255, 255, 255),
            bd + 230 + (i * 79),
            bd + 63,
            ALLEGRO_ALIGN_CENTER,
            "%d",
            i + 1
        );
    }

    // Textos
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        bd + 106,
        bd + 155,
        ALLEGRO_ALIGN_CENTER,
        "CPU"
    );

    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        bd + 106,
        bd + 213,
        ALLEGRO_ALIGN_CENTER,
        "Disco"
    );

    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        bd + 106,
        bd + 270,
        ALLEGRO_ALIGN_CENTER,
        "Rodadas"
    );

    // --------------------------------------------------
    // Gráfico
    // --------------------------------------------------

    static const short espaco = 75;

    al_draw_filled_rectangle(
        bd, LHM + bd, LARGURA - bd, ALTURA - bd, al_map_rgb(15, 15, 15)
    );

    al_draw_rectangle(
        bd, LHM + bd, LARGURA - bd, ALTURA - bd, al_map_rgb(144, 144, 144), 5
    );

    // Linha de CPU
    al_draw_filled_rectangle(
        bd * 3,
        LHI - espaco - 3,
        LARGURA - bd * 3,
        LHI - espaco + 3,
        al_map_rgb(100, 100, 100)
    );

    // Linha de IO
    al_draw_filled_rectangle(
        bd * 3,
        LHI + espaco - 3,
        LARGURA - bd * 3,
        LHI + espaco + 3,
        al_map_rgb(100, 100, 100)
    );

    // Texto de CPU
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) - 125,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de CPU"
    );

    // Texto de IO
    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) + 35,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de IO"
    );
}
