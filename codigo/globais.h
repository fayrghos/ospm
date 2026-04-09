#pragma once

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