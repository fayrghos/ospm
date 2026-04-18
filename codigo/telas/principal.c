#include "../globais.h"
#include "../utilidades.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include <stdio.h>
#include <string.h>

// Horizontais
#define LHM ALTURA / 2
#define LHI ALTURA / 4 + LHM

static void
desenhar_processo(int x, int y, ALLEGRO_FONT *fonte, int id, Globais globs) {
    al_draw_filled_circle(x, y, 30, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(
        x,
        y,
        27,
        id < globs.ind_processo_atual ? traduzir_cor(id)
                                      : al_map_rgb(50, 50, 50)
    );

    char id_txt[20] = "";
    if (id < globs.ind_processo_atual) {
        sprintf(id_txt, "%d", id + 1);
    }

    desenhar_texto_cen(x, y, fonte, id_txt);
}

static void desenhar_tabela(
    int x, int y, ALLEGRO_FONT *fonte_p, ALLEGRO_FONT *fonte_m, Globais globs
) {
    x -= 573 / 2;
    y -= 292 / 2;

    // Barra princial
    al_draw_filled_rectangle(x, y, x + 573, y + 118, al_map_rgb(84, 84, 84));

    // Barrinhas
    for (int i = 0; i < 3; i++) {
        al_draw_filled_rectangle(
            x,
            y + 123 + (i * 58),
            x + 573,
            y + 176 + (i * 58),
            al_map_rgb(84, 84, 84)
        );
    }

    // Paginador
    al_draw_filled_rectangle(
        x + 24, y + 25, x + 142, y + 93, al_map_rgb(255, 255, 255)
    );
    al_draw_filled_rectangle(
        x + 27, y + 28, x + 139, y + 90, al_map_rgb(29, 29, 32)
    );

    // Bolinhas
    for (int i = 0; i < 5; i++) {
        desenhar_processo(
            x + 181 + 20 + (i * 80), y + 33 + 28, fonte_m, i, globs
        );
    }

    // Linhas
    desenhar_texto_cen(x + 82, y + 149, fonte_p, "CPU");
    desenhar_texto_cen(x + 82, y + 207, fonte_p, "Disco");
    desenhar_texto_cen(x + 82, y + 265, fonte_p, "Rodadas");

    char cpu_txt[20];
    char disco_txt[20];
    char rodad_txt[20];

    for (int i = 0; i < 5; i++) {
        if (i >= globs.q_processos) {
            strcpy(cpu_txt, "–");
            strcpy(disco_txt, "–");
            strcpy(rodad_txt, "–");
        } else {
            sprintf(
                cpu_txt, "%d%s", globs.processos_const[i].tempo_de_cpu, "s"
            );

            sprintf(
                disco_txt, "%d%s", globs.processos_const[i].tempo_de_IO, "s"
            );

            sprintf(rodad_txt, "%d", globs.processos_const[i].quant_rodadas);
        }

        desenhar_texto_cen(x + 200 + (i * 80), y + 149, fonte_p, cpu_txt);
        desenhar_texto_cen(x + 200 + (i * 80), y + 207, fonte_p, disco_txt);
        desenhar_texto_cen(x + 200 + (i * 80), y + 265, fonte_p, rodad_txt);
    }
}

void desenhar_principal(
    ALLEGRO_FONT *fonte_p, ALLEGRO_FONT *fonte_m, Globais globs
) {
    static const short bd = 30;

    // --------------------------------------------------
    // Tabela
    // --------------------------------------------------

    al_draw_filled_rectangle(
        bd, bd, LARGURA / 2 - bd, ALTURA / 2 - bd, al_map_rgb(52, 52, 54)
    );

    desenhar_tabela(LARGURA / 4, ALTURA / 4, fonte_p, fonte_m, globs);

    al_draw_text(
        fonte_p,
        al_map_rgb(255, 255, 255),
        bd + 107,
        bd + 65,
        ALLEGRO_ALIGN_CENTER,
        "Pág. 1"
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
        fonte_p,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) - 125,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de CPU"
    );

    // Texto de IO
    al_draw_text(
        fonte_p,
        al_map_rgb(255, 255, 255),
        LARGURA - 90,
        (ALTURA / 2) + (ALTURA / 4) + 35,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de Disco"
    );
}
