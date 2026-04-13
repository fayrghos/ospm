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
#include <stdlib.h>
#include <string.h>

void manusear_insercao(ALLEGRO_EVENT ev, Globais *globs) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            rodar_inteiro(0, 2, &globs->ind_botao_atual, +1);
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
            rodar_inteiro(0, 2, &globs->ind_botao_atual, -1);
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            strcpy(globs->txt_erro, "");
            globs->q_processos = atoi(globs->q_processos_txt);
            globs->so_info.quantum = atoi(globs->so_info.txt_quantum);
            globs->so_info.tempo_total = atoi(globs->so_info.txt_tempo_total);

            if (globs->q_processos == 0 || globs->so_info.quantum == 0 ||
                globs->so_info.tempo_total == 0) {
                strcpy(globs->txt_erro, "Preencha todos os campos.");
                return;
            }

            if (globs->q_processos > 20) {
                strcpy(
                    globs->txt_erro,
                    "A quantidade de processos não pode ser maior que 20."
                );
                return;
            }

            if (globs->q_processos > 0) {
                globs->ind_botao_atual = 0;
                globs->tela_atual = T_DEFINIR;
            }
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
            globs->easter_egg = true;
        }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
            globs->easter_egg = false;
        }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        switch (globs->ind_botao_atual) {
        case 0:
            inserir_texto(ev, globs->q_processos_txt);
            break;

        case 1:
            inserir_texto(ev, globs->so_info.txt_quantum);
            break;

        case 2:
            inserir_texto(ev, globs->so_info.txt_tempo_total);
            break;
        }
    }
}

void desenhar_insercao(
    Globais globs,
    ALLEGRO_BITMAP *danael,
    ALLEGRO_BITMAP *totem,
    ALLEGRO_FONT *fonte32,
    ALLEGRO_FONT *fonte72,
    ALLEGRO_TIMER *timer
) {
    if (globs.easter_egg) {
        al_draw_scaled_bitmap(
            danael, 0, 0, 1024, 1053, 0, 0, LARGURA, ALTURA, 0
        );
        return;
    }

    al_draw_bitmap(totem, -65, ALTURA - 325, 0);

    desenhar_botao(
        LARGURA / 2,
        ALTURA / 2 - 200,
        "Total de Processos",
        globs.q_processos_txt,
        globs.ind_botao_atual == 0,
        fonte32,
        fonte72,
        timer
    );

    desenhar_botao(
        LARGURA / 2,
        ALTURA / 2,
        "Quantum da CPU",
        globs.so_info.txt_quantum,
        globs.ind_botao_atual == 1,
        fonte32,
        fonte72,
        timer
    );

    desenhar_botao(
        LARGURA / 2,
        ALTURA / 2 + 200,
        "Tempo de Execução Total",
        globs.so_info.txt_tempo_total,
        globs.ind_botao_atual == 2,
        fonte32,
        fonte72,
        timer
    );
}