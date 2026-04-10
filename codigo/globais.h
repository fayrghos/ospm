#pragma once

#include <allegro5/color.h>
#include <stdbool.h>

// Por algum motivo, o clang-tidy reclama quando isso é int
// Bora deixar pixel sempre double então
#define LARGURA 1366.0
#define ALTURA 768.0

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
    bool q_processos;
    char q_processos_txt[30];
    bool easter_egg;
} Globais;

/*
 * Gerencia o suporte a combinações de teclado.
 */
typedef struct {
    bool ctrl;
    bool shift;
    bool alt;
} Modificadores;

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

ALLEGRO_COLOR traduzir_cor_proc(ECorProcesso cor);