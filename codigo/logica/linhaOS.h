#pragma once

#include "fila.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include <stdlib.h>

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
    Gradiente grad_exec[80];
    Gradiente grad_io[80];
    SO so_info;
    Processo processos[8];
    int total_exec;
    int total_IO;
    int total_processos;
    float larg_x;

    int ind_processo_atual;
    int ind_botao_atual;

    char txt_cpu[30];
    char txt_disco[30];
    char txt_rodada[30];
} Ospm;

void desenhar_linha_de_execucao(Ospm *os, ALLEGRO_FONT *fonte);

void exec(Ospm *os);