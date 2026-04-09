#include "../globais.h"
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <stdbool.h>

void manusear_modificadores(ALLEGRO_EVENT ev, Modificadores *mods) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LCTRL:
        case ALLEGRO_KEY_RCTRL:
            mods->ctrl = true;
            break;

        case ALLEGRO_KEY_LSHIFT:
        case ALLEGRO_KEY_RSHIFT:
            mods->shift = true;
            break;

        case ALLEGRO_KEY_ALT:
            mods->alt = true;
            break;
        }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_LCTRL:
        case ALLEGRO_KEY_RCTRL:
            mods->ctrl = false;
            break;

        case ALLEGRO_KEY_LSHIFT:
        case ALLEGRO_KEY_RSHIFT:
            mods->shift = false;
            break;

        case ALLEGRO_KEY_ALT:
            mods->alt = false;
            break;
        }
    }
}