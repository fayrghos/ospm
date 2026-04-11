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
        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            strcpy(globs->txt_erro, "");
            globs->q_processos = atoi(globs->q_processos_txt);

            if (globs->q_processos == 0) {
                strcpy(
                    globs->txt_erro, "A quantidade não pode ficar em branco."
                );
                return;
            }

            if (globs->q_processos > 20) {
                strcpy(
                    globs->txt_erro, "A quantidade não pode ser maior que 20."
                );
                return;
            }

            if (globs->q_processos > 0) {
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
        inserir_texto(ev, globs->q_processos_txt);
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
        ALTURA / 2,
        "Total de Processos",
        globs.q_processos_txt,
        true,
        fonte32,
        fonte72,
        timer
    );
}