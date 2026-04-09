#pragma once

#include <stdbool.h>

// Por algum motivo, o clang-tidy reclama quando isso é int
// Bora deixar pixel sempre double então
#define LARGURA 1366.0
#define ALTURA 768.0

typedef enum {
    T_INTRO,
    T_INSERIR,
    T_PRINCIPAL,
} ETela;

typedef struct {
    bool q_processos;
    char q_processos_txt[30];
} Globais;