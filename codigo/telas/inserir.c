#include "../globais.h"
#include "../logica/digitacao.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/timer.h>

void manusear_insercao(ALLEGRO_EVENT ev, Globais *globs) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            globs->q_processos = atoi(globs->q_processos_txt);

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

    al_draw_text(
        fonte72,
        al_map_rgb(255, 255, 255),
        LARGURA / 2,
        ALTURA / 2 - 150,
        ALLEGRO_ALIGN_CENTER,
        "Insira o Total de Processos"
    );

    al_draw_filled_rounded_rectangle(
        LARGURA / 2 - 300,
        ALTURA / 2 - 20,
        LARGURA / 2 + 300,
        ALTURA / 2 + 100,
        30,
        30,
        al_map_rgb(52, 52, 54)
    );

    // Piscada do cursor
    if (globs.q_processos_txt[0] == '\0' &&
        al_get_timer_count(timer) % 20 <= 10) {
        al_draw_text(
            fonte72,
            al_map_rgb(255, 255, 255),
            LARGURA / 2,
            ALTURA / 2,
            ALLEGRO_ALIGN_CENTER,
            "_"
        );
    }

    al_draw_text(
        fonte72,
        al_map_rgb(255, 255, 255),
        LARGURA / 2,
        ALTURA / 2,
        ALLEGRO_ALIGN_CENTER,
        globs.q_processos_txt
    );
}