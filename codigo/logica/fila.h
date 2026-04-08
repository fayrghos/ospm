#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

typedef struct {
    int tempo_exe;
    int tempo_disc;
    ALLEGRO_COLOR cor;
} Processo;

typedef struct No {
    Processo processo;
    struct No * prox_no;
} No;

typedef struct {
    No * inicio;
    No * fim;
} Fila;

void inserir_fila(Fila *fila, Processo p);
Processo remover_fila(Fila *fila);
int isempty(Fila * fila);
Processo pegar_inicio(Fila fila);
