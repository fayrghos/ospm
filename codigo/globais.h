#pragma once

#include "logica/fila.h"
#include <allegro5/color.h>
#include <allegro5/allegro_audio.h>
#include <stdbool.h>

// Por algum motivo, o clang-tidy reclama quando isso é int
// Bora deixar pixel sempre double então
#define LARGURA 1366.0
#define ALTURA 768.0

typedef struct {
    float x0, x1;
    ALLEGRO_COLOR cor;
    int fila;
    int tempo_processo;
} Gradiente;

typedef struct {
    int quantum;
    char txt_quantum[20];

    int tempo_total;
    char txt_tempo_total[20];

    Fila fila_IO;
    Fila fila_exec;
} SO;

/*
 * Enumeração de todas as telas fixas do programa.
 */
typedef enum {
    T_INTRO,
    T_INSERIR,
    T_DEFINIR,
    T_PRINCIPAL,
} ETela;

/*
 * Gerencia o suporte a combinações de teclado.
 */
typedef struct {
    bool ctrl;
    bool shift;
    bool alt;
} Modificadores;

/*
 * Guarda as variáveis que são acessíveis no programa inteiro.
 */
typedef struct {
    Modificadores mods;

    ETela tela_atual;
    int q_processos;
    char q_processos_txt[30];
    bool easter_egg;
    char txt_erro[200];
    int frame_contagem;

    bool modo_rapido;

    Gradiente grad_exec[80];
    Gradiente grad_io[80];
    SO so_info;

    Processo processos[20];
    Processo processos_const[20];

    int total_exec;
    int total_IO;
    float larg_x_exec;
    float larg_x_IO;
    int pivo;
    int total_io_analise;
    int total_exec_analise;

    int ind_processo_atual;
    int ind_botao_atual;
    int ind_tabela_atual;
    int ind_maior_tabela;
    float escala;

    char txt_cpu[30];
    char txt_disco[30];
    char txt_rodada[30];

    Processo *graf_primeiro;
    int graf_pagina_atual;
    ALLEGRO_SAMPLE *audio;
} Globais;

#define MAX_CORES 10

/*
 * Transforma um ID de processo em sua respectiva cor no Allegro.
 */
ALLEGRO_COLOR traduzir_cor(int cor);
