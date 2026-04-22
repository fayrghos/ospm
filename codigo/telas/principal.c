#include "../cores.h"
#include "../globais.h"
#include "../utilidades.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include <string.h>

// Horizontais
#define LHM ALTURA / 2
#define LHI ALTURA / 4 + LHM

static void
desenhar_processo(int x, int y, ALLEGRO_FONT *fonte, int id, Globais globs) {
    al_draw_filled_circle(x, y, 30, COR_BRANCO);
    al_draw_filled_circle(
        x, y, 27, id < globs.ind_processo_atual ? traduzir_cor(id) : COR_CINZA
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
    al_draw_filled_rectangle(x, y, x + 573, y + 118, COR_CLARO);

    // Barrinhas
    for (int i = 0; i < 3; i++) {
        al_draw_filled_rectangle(
            x, y + 123 + (i * 58), x + 573, y + 176 + (i * 58), COR_CLARO
        );
    }

    // Paginador
    al_draw_filled_rectangle(x + 24, y + 25, x + 142, y + 93, COR_BRANCO);
    al_draw_filled_rectangle(x + 27, y + 28, x + 139, y + 90, COR_FUNDO);

    // Bolinhas
    for (int i = 0; i < 5; i++) {
        desenhar_processo(
            x + 181 + 20 + (i * 80),
            y + 33 + 28,
            fonte_m,
            i + 5 * globs.ind_tabela_atual,
            globs
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
        int i_offs = i + 5 * globs.ind_tabela_atual;

        if (i_offs >= globs.q_processos) {
            strcpy(cpu_txt, "–");
            strcpy(disco_txt, "–");
            strcpy(rodad_txt, "–");
        } else {
            sprintf(
                cpu_txt, "%d%s", globs.processos_const[i_offs].tempo_de_cpu, "s"
            );

            sprintf(
                disco_txt,
                "%d%s",
                globs.processos_const[i_offs].tempo_de_IO,
                "s"
            );

            sprintf(
                rodad_txt, "%d", globs.processos_const[i_offs].quant_rodadas
            );
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

    // Fundo
    al_draw_filled_rectangle(
        bd, bd, LARGURA / 2 - bd, ALTURA / 2 - bd, COR_CINZA
    );

    desenhar_tabela(LARGURA / 4, ALTURA / 4, fonte_p, fonte_m, globs);

    al_draw_textf(
        fonte_p,
        COR_BRANCO,
        bd + 107,
        bd + 65,
        ALLEGRO_ALIGN_CENTER,
        "Pág. %d",
        globs.ind_tabela_atual + 1
    );

    // --------------------------------------------------
    // Tabelinha
    // --------------------------------------------------

    // Fundo
    al_draw_filled_rectangle(
        LARGURA / 2 + bd, bd, LARGURA / 2 + 300, LHM - bd, COR_CINZA
    );

    // Placa
    al_draw_filled_rectangle(
        LARGURA / 2 + bd + 20,
        bd + 15,
        LARGURA / 2 + 280,
        LHM - bd - 15,
        COR_CLARO
    );

    // Uso de CPU
    al_draw_text(
        fonte_p, COR_BRANCO, LARGURA / 2 + 2 * bd, bd * 2, 0, "· Uso CPU"
    );
    al_draw_textf(
        fonte_p,
        COR_BRANCO,
        LARGURA / 2 + 293 - bd,
        bd * 2,
        ALLEGRO_ALIGN_RIGHT,
        "%.1f%%",
        globs.so_info.uso_cpu * 100
    );

    // Média de Espera
    al_draw_text(
        fonte_p, COR_BRANCO, LARGURA / 2 + 2 * bd, bd * 3, 0, "· Média Espera"
    );
    al_draw_textf(
        fonte_p,
        COR_BRANCO,
        LARGURA / 2 + 293 - bd,
        bd * 3,
        ALLEGRO_ALIGN_RIGHT,
        "%.1fs",
        0.0
    );

    // Finalizados
    al_draw_text(
        fonte_p, COR_BRANCO, LARGURA / 2 + 2 * bd, bd * 4, 0, "· Finalizados"
    );
    al_draw_textf(
        fonte_p,
        COR_BRANCO,
        LARGURA / 2 + 293 - bd,
        bd * 4,
        ALLEGRO_ALIGN_RIGHT,
        "%d",
        0
    );

    // --------------------------------------------------
    // Gráfico
    // --------------------------------------------------

    static const short espaco = 75;

    al_draw_filled_rectangle(
        bd, LHM + bd, LARGURA - bd, ALTURA - bd, COR_CINZA
    );

    al_draw_filled_rectangle(
        bd + 15, LHM + bd + 15, LARGURA - bd - 15, ALTURA - bd - 15, COR_PRETO
    );

    // Linha de CPU
    al_draw_filled_rectangle(
        bd * 3, LHI - espaco - 3, LARGURA - bd * 3, LHI - espaco + 3, COR_CLARO
    );

    // Linha de IO
    al_draw_filled_rectangle(
        bd * 3, LHI + espaco - 3, LARGURA - bd * 3, LHI + espaco + 3, COR_CLARO
    );

    // Texto de CPU
    al_draw_text(
        fonte_p,
        COR_BRANCO,
        LARGURA - bd * 3,
        LHI - espaco - 40,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de CPU"
    );

    // Texto de Disco
    al_draw_text(
        fonte_p,
        COR_BRANCO,
        LARGURA - bd * 3,
        LHI + espaco - 40,
        ALLEGRO_ALIGN_RIGHT,
        "Linha de Disco"
    );
}

void manusear_principal(ALLEGRO_EVENT ev, Globais *globs) {
    globs->so_info.uso_cpu =
        globs->so_info.tempo_total > 0
            ? (float)globs->total_exec_analise / globs->q_processos
            : 0;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_TAB) {
        if (globs->mods.shift) {
            rodar_inteiro(
                0, globs->ind_maior_tabela, &globs->ind_tabela_atual, -1
            );
            return;
        }

        rodar_inteiro(0, globs->ind_maior_tabela, &globs->ind_tabela_atual, +1);
    }
}
