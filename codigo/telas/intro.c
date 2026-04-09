#include "../globais.h"
#include <allegro5/allegro_video.h>
#include <allegro5/bitmap.h>

void desenhar_intro(ALLEGRO_VIDEO *intro) {
    ALLEGRO_BITMAP *frame = al_get_video_frame(intro);

    if (frame) {
        al_draw_scaled_bitmap(
            frame,
            0,
            0,
            al_get_bitmap_width(frame),
            al_get_bitmap_height(frame),
            0,
            0,
            LARGURA,
            ALTURA,
            0
        );
    }
}