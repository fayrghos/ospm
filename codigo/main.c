#include "logica/digitacao.h"
#include "logica/tabela.h"
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
#include <string.h>
#include <unistd.h>

// Por algum motivo, o clang-tidy reclama quando isso é int
// Bora deixar pixel sempre double então
#define LARGURA 1366.0
#define ALTURA 768.0

typedef struct {
    int total_processos;
    short n_tela;
    bool escrever;
    int quantun;

} Dados;

typedef struct {
    int temp_cpu;
    int temp_IO;
    int quant_rodadas;
    int tempo_total;
} Processos;

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
    ALLEGRO_EVENT evento;

    ALLEGRO_VIDEO* video_intro = al_open_video("./materiais/intro/intro.ogv");
    al_start_video(video_intro, al_get_default_mixer());

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 24.0);
    al_start_timer(timer);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_register_event_source(fila, al_get_video_event_source(video_intro));

    Dados dados = {
        .escrever = true,
        .n_tela = 1,
    };

    ALLEGRO_FONT *fonte18 =
        carregar_fonte("./materiais/fontes/LiberationSans.ttf", 18);

    ALLEGRO_FONT *fonte72 =
        carregar_fonte("./materiais/fontes/LiberationSans.ttf", 72);

    ALLEGRO_BITMAP *totem = al_load_bitmap("./materiais/imagens/totem.png");

    ALLEGRO_BITMAP *danael = carregar_bitmap("./materiais/imagens/danael.png");

    ALLEGRO_BITMAP *malha = NULL;

    // --------------------------------------------------
    // Controle do Programa
    // --------------------------------------------------
    bool intro = true;
    bool redesenhar = true;
    bool easter_egg = false;
    ALLEGRO_BITMAP *frame;

    char texto[256] = "";
    const char *titulos[] = {"Processos", "CPU", "Disco"};

    for (;;) {
        al_wait_for_event(fila, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if(evento.type == ALLEGRO_EVENT_VIDEO_FINISHED) {
            intro = false;
            al_close_video(video_intro);
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                dados.escrever = false;
                dados.total_processos = atoi(texto);

                if (dados.total_processos > 0) {
                    dados.n_tela++;
                    malha = al_load_bitmap("./materiais/imagens/malha.png");
                }
            }


            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (dados.n_tela > 1) {
                    dados.n_tela--;
                    al_destroy_bitmap(malha);

                    dados.escrever = true;
                    // Quanto o usuário voltava ao menu com ESC, a string tava
                    // cheia. Botei isso pra encher ela de '\0'
                    memset(texto, 0, sizeof(texto));
                }
            }
            if (evento.keyboard.keycode == ALLEGRO_KEY_D && dados.n_tela == 1) {
                easter_egg = true;
            }
        }

        if (evento.type == ALLEGRO_EVENT_KEY_UP) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_D) {
                easter_egg = false;
            }
        }

        if (dados.escrever) {
            if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                inserir_texto(evento, texto);
            }
        }

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            redesenhar = true;
        }

        if (redesenhar && al_event_queue_is_empty(fila)) {
            al_clear_to_color(al_map_rgb(255, 255, 255));

            switch (dados.n_tela) {
            case 1:
                if (easter_egg) {
                    al_draw_scaled_bitmap(
                        danael, 0, 0, 1024, 1053, 0, 0, LARGURA, ALTURA, 0
                    );
                }

                if(intro) {
                    frame = al_get_video_frame(video_intro);

                if(frame) {
                    al_draw_scaled_bitmap(
                        frame, 0, 0, al_get_bitmap_width(frame), al_get_bitmap_height(frame), 0, 0, LARGURA, ALTURA, 0
                    );
                }
            } else {
                    al_draw_filled_rectangle(
                        0, 0, LARGURA, ALTURA, al_map_rgb(29, 29, 32)
                    );

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
                    if (texto[0] == '\0' &&
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
                        texto
                    );
                }
                break;

            case 2:
                al_draw_scaled_bitmap(
                    malha, 0, 0, 1920, 1080, 0, 0, LARGURA, ALTURA, 0
                );

                break;

            default:
                break;
            }

            al_flip_display();
            redesenhar = false;
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