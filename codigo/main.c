#include "globais.h"
#include "logica/digitacao.h"
#include "logica/modificadores.h"
#include "telas/inserir.h"
#include "telas/intro.h"
#include "telas/principal.h"
#include "utilidades.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>
#include <allegro5/altime.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // --------------------------------------------------
    // Inicialização do Allegro
    // --------------------------------------------------
    if (!al_init()) {
        fprintf(stderr, "Não foi possível iniciar o Allegro.\n");
        exit(1);
    }

    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_video_addon();

    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    ALLEGRO_DISPLAY *tela = al_create_display(LARGURA, ALTURA);
    al_set_window_title(tela, "OSPM");

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    ALLEGRO_EVENT ev;

    ALLEGRO_VIDEO *intro = al_open_video("./materiais/intro/intro.ogv");
    al_start_video(intro, al_get_default_mixer());

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 24.0);
    al_start_timer(timer);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_video_event_source(intro));

    // --------------------------------------------------
    // Carregamento de Materiais
    // --------------------------------------------------
    ALLEGRO_FONT *fonte18 =
        carregar_fonte("./materiais/fontes/LiberationSans.ttf", 18);

    ALLEGRO_FONT *fonte72 =
        carregar_fonte("./materiais/fontes/LiberationSans.ttf", 72);

    ALLEGRO_BITMAP *totem = carregar_bitmap("./materiais/imagens/totem.png");

    ALLEGRO_BITMAP *danael = carregar_bitmap("./materiais/imagens/danael.png");

    // --------------------------------------------------
    // Controle do Programa
    // --------------------------------------------------
    Globais globs = {
        .tela_atual = T_INTRO // T_INSERIR para pular
    };

    if (globs.tela_atual != T_INTRO) {
        al_close_video(intro);
    }

    Modificadores mods = {};

    for (;;) {
        al_wait_for_event(fila, &ev);
        manusear_modificadores(ev, &mods);

        // Fechamento do programa
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ||
            mods.ctrl && (ev.keyboard.keycode == ALLEGRO_KEY_Q ||
                          ev.keyboard.keycode == ALLEGRO_KEY_W)) {
            break;
        }

        // Fechamento da intro
        if (ev.type == ALLEGRO_EVENT_VIDEO_FINISHED) {
            al_close_video(intro);
            globs.tela_atual = T_INSERIR;
        }

        // O fundo do programa vai ser sempre esse cinza
        al_clear_to_color(al_map_rgb(29, 29, 32));

        switch (globs.tela_atual) {
        case T_INTRO:
            desenhar_intro(intro);
            break;

        case T_INSERIR:
            manusear_insercao(ev, &globs);
            desenhar_insercao(globs, danael, totem, fonte72, timer);
            break;

        case T_PRINCIPAL:
            desenhar_principal();
            break;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_flip_display();
        }
    }

    // --------------------------------------------------
    // Limpeza
    // --------------------------------------------------
    al_destroy_font(fonte18);
    al_destroy_font(fonte72);

    al_destroy_bitmap(totem);
    al_destroy_bitmap(danael);

    al_destroy_display(tela);
    al_destroy_event_queue(fila);
    al_destroy_timer(timer);

    exit(0);
}