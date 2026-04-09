#include <allegro5/allegro5.h>
#include <allegro5/color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include "fila.h"

typedef struct {
    float x0, x1;
    ALLEGRO_COLOR cor;
    int fila;
} Gradiente;

typedef struct {
    int quantum;
    int tempo_total;
    Fila fila_IO;
    Fila fila_exec;
} SO;

typedef struct {
    Gradiente grad_exec [80];
    Gradiente grad_io [80];
    SO so_info;
    Processo processos[8];
    int total_exec;
    int total_IO;
    int total_processos;
    float larg_x;
} Ospm;

void desenhar_linha_de_execucao(Ospm *os, ALLEGRO_FONT *fonte);

void exec(Ospm *os);