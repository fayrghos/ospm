#include "../cores.h"
#include "../globais.h"
#include "../logica/digitacao.h"
#include "../utilidades.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>
#include <stdlib.h>
#include <string.h>

static void desenhar_botaozinho(
    ALLEGRO_FONT *fonte, bool selecionado, float x, float y, char *texto
) {
    if (selecionado) {
        al_draw_filled_rounded_rectangle(
            x - 203, y - 33, x + 203, y + 33, 20, 20, COR_SELECAO
        );
    }

    al_draw_filled_rounded_rectangle(
        x - 200, y - 30, x + 200, y + 30, 20, 20, COR_CINZA
    );

    desenhar_texto_cen(x, y, fonte, texto);
}

void manusear_inicial(ALLEGRO_EVENT ev, Globais *globs) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            rodar_inteiro(0, 2, &globs->ind_botao_atual, +1);
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
            rodar_inteiro(0, 2, &globs->ind_botao_atual, -1);
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_TAB) {
            if (globs->mods.shift) {
                rodar_inteiro(0, 3, (int *)&globs->modo_escal, -1);
            } else {
                rodar_inteiro(0, 3, (int *)&globs->modo_escal, +1);
            }
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
                    "A quantia de processos não pode ser maior que 20."
                );
                return;
            }

            if (globs->q_processos > 0) {
                for (int i = 1; i < globs->q_processos; i++) {
                    if (i % 5 == 0) {
                        globs->ind_maior_tabela++;
                    }
                }

                globs->ind_botao_atual = 0;
                globs->tela_atual = T_PROCESSOS;
            }
        }

        if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
            globs->easter_egg = true;
            al_play_sample(globs->audio, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
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

void desenhar_inicial(
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

    al_draw_scaled_bitmap(
        totem, 0, 0, 325, 325, -20, ALTURA - 160, 150, 150, 0
    );

    desenhar_botao(
        LARGURA / 2 + 230,
        ALTURA / 2 - 180,
        "Total de Processos",
        globs.q_processos_txt,
        globs.ind_botao_atual == 0,
        fonte32,
        fonte72,
        timer
    );

    desenhar_botao(
        LARGURA / 2 + 230,
        ALTURA / 2,
        "Quantum da CPU",
        globs.so_info.txt_quantum,
        globs.ind_botao_atual == 1,
        fonte32,
        fonte72,
        timer
    );

    desenhar_botao(
        LARGURA / 2 + 230,
        ALTURA / 2 + 180,
        "Tempo de Execução Total",
        globs.so_info.txt_tempo_total,
        globs.ind_botao_atual == 2,
        fonte32,
        fonte72,
        timer
    );

    desenhar_botaozinho(
        fonte32,
        globs.modo_escal == ME_ROBIN,
        LARGURA / 2 - 320,
        ALTURA / 2 - 120,
        "Round Robin"
    );

    desenhar_botaozinho(
        fonte32,
        globs.modo_escal == ME_PRIMEIRO,
        LARGURA / 2 - 320,
        ALTURA / 2 - 40,
        "Primeiro Servir"
    );

    desenhar_botaozinho(
        fonte32,
        globs.modo_escal == ME_JOB,
        LARGURA / 2 - 320,
        ALTURA / 2 + 40,
        "Menor Job"
    );

    desenhar_botaozinho(
        fonte32,
        globs.modo_escal == ME_PRIORIDADE,
        LARGURA / 2 - 320,
        ALTURA / 2 + 120,
        "Por Prioridade"
    );
}
