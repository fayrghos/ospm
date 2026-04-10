#include "../globais.h"
#include "../logica/digitacao.h"
#include "../utilidades.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>
#include <stdio.h>

void _desenhar_botao(
    float x,
    float y,
    char *titulo,
    char *escrita,
    bool selecionado,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
) {
    al_draw_text(
        fonte_p,
        al_map_rgb(255, 255, 255),
        x - 300,
        y - 100,
        ALLEGRO_ALIGN_LEFT,
        titulo
    );

    if (selecionado) {
        al_draw_filled_rounded_rectangle(
            x - 303, y - 53, x + 303, y + 53, 20, 20, al_map_rgb(222, 221, 218)
        );
    }

    al_draw_filled_rounded_rectangle(
        x - 300, y - 50, x + 300, y + 50, 20, 20, al_map_rgb(52, 52, 54)
    );

    if (selecionado && al_get_timer_count(timer) % 20 >= 10 &&
        escrita[0] == '\0') {
        al_draw_text(
            fonte_g,
            al_map_rgb(255, 255, 255),
            x,
            y - 40,
            ALLEGRO_ALIGN_CENTER,
            "_"
        );
    }

    al_draw_text(
        fonte_g,
        al_map_rgb(255, 255, 255),
        x,
        y - 40,
        ALLEGRO_ALIGN_CENTER,
        escrita
    );
}

void _desenhar_processo(
    float x,
    float y,
    int id,
    ECorProcesso cor,
    ALLEGRO_FONT *fonte,
    Globais globs
) {
    al_draw_filled_rounded_rectangle(
        x - 120, y - 130, x + 120, y + 130, 20, 20, al_map_rgb(52, 52, 54)
    );

    al_draw_filled_circle(x, y - 35, 60, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(
        x, y - 35, 56, traduzir_cor_proc(globs.ind_processo_atual % 10)
    );

    char proc_txt[30] = "";
    sprintf(proc_txt, "Processo %d", globs.ind_processo_atual + 1);

    al_draw_text(
        fonte,
        al_map_rgb(255, 255, 255),
        x,
        y + 50,
        ALLEGRO_ALIGN_CENTER,
        proc_txt
    );
}

void manusear_definicao(ALLEGRO_EVENT ev, Globais *globs) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_DOWN:
            rodar_inteiro(0, 2, &globs->ind_botao_atual, +1);
            break;

        case ALLEGRO_KEY_UP:
            rodar_inteiro(0, 2, &globs->ind_botao_atual, -1);
            break;

        case ALLEGRO_KEY_ENTER:
            globs->ind_processo_atual++;
            globs->ind_botao_atual = 0;

            if (globs->ind_processo_atual >= globs->q_processos) {
                globs->tela_atual = T_PRINCIPAL;
                return;
            }

            // TODO: Lógica de salvar lá no globs/globs

            memset(globs->txt_cpu, 0, sizeof(globs->txt_cpu));
            memset(globs->txt_disco, 0, sizeof(globs->txt_disco));
            memset(globs->txt_rodada, 0, sizeof(globs->txt_rodada));
        }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        switch (globs->ind_botao_atual) {
        case 0:
            inserir_texto(ev, globs->txt_cpu);
            break;

        case 1:
            inserir_texto(ev, globs->txt_disco);
            break;

        case 2:
            inserir_texto(ev, globs->txt_rodada);
            break;
        }
    }
}

void desenhar_definicao(
    Globais globs,
    ALLEGRO_BITMAP *danael,
    ALLEGRO_BITMAP *totem,
    ALLEGRO_FONT *fonte_p,
    ALLEGRO_FONT *fonte_g,
    ALLEGRO_TIMER *timer
) {
    _desenhar_botao(
        LARGURA / 2 + 180,
        ALTURA / 2 - 180,
        "Tempo em CPU",
        globs.txt_cpu,
        globs.ind_botao_atual == 0,
        fonte_p,
        fonte_g,
        timer
    );

    _desenhar_botao(
        LARGURA / 2 + 180,
        ALTURA / 2,
        "Tempo em Disco",
        globs.txt_disco,
        globs.ind_botao_atual == 1,
        fonte_p,
        fonte_g,
        timer
    );

    _desenhar_botao(
        LARGURA / 2 + 180,
        ALTURA / 2 + 180,
        "Número de Rodadas",
        globs.txt_rodada,
        globs.ind_botao_atual == 2,
        fonte_p,
        fonte_g,
        timer
    );

    _desenhar_processo(300, ALTURA / 2, 1, 0, fonte_p, globs);

    // Piscada do cursor
    if (globs.q_processos_txt[0] == '\0' &&
        al_get_timer_count(timer) % 20 <= 10) {
        al_draw_text(
            fonte_g,
            al_map_rgb(255, 255, 255),
            LARGURA / 2,
            ALTURA / 2,
            ALLEGRO_ALIGN_CENTER,
            "_"
        );
    }
}