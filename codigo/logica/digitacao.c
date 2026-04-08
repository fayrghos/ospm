#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <string.h>

void inserir_texto(ALLEGRO_EVENT ev, char *texto) {
    if (ev.keyboard.unichar >= 48 && ev.keyboard.unichar <= 57) {
        texto[strlen(texto)] = (char)ev.keyboard.unichar;
    }

    else if ((char)ev.keyboard.unichar == '\b') {
        if (strlen(texto) > 0) {
            texto[strlen(texto) - 1] = '\0';
        }
    }
}