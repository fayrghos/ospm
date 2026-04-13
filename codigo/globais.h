#pragma once

#include "logica/fila.h"
#include <allegro5/color.h>
#include <stdbool.h>


// Por algum motivo, o clang-tidy reclama quando isso é int
// Bora deixar pixel sempre double então
#define LARGURA 1366.0
#define ALTURA 768.0

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
 * Guarda as variáveis que são acessíveis no programa inteiro.
 */
typedef struct {
    ETela tela_atual;
    int q_processos;
    char q_processos_txt[30];
    bool easter_egg;
    char txt_erro[200];

    Gradiente grad_exec[80];
    Gradiente grad_io[80];
    SO so_info;
    Processo processos[20];
    int total_exec;
    int total_IO;
    float larg_x_exec;
    float larg_x_IO;


    int ind_processo_atual;
    int ind_botao_atual;

    char txt_cpu[30];
    char txt_disco[30];
    char txt_rodada[30];
} Globais;

/*
 * Gerencia o suporte a combinações de teclado.
 */
typedef struct {
    bool ctrl;
    bool shift;
    bool alt;
} Modificadores;

#define MAX_CORES 10

/*
 * Enumeração de cores reservada para processos.
 */
typedef enum {
    C_VERMELHO,
    C_VERDE,
    C_AZUL,
    C_CINZA,
    C_LARANJA,
    C_CIANO,
    C_MAGENTA,
    C_AMARELO,
    C_MARROM,
    C_PRETO
} ECorProcesso;

/*
 * Transforma um ECorProcesso em sua respectiva cor no Allegro.
 */
ALLEGRO_COLOR traduzir_cor_proc(ECorProcesso cor);