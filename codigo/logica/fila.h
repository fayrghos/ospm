#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

typedef struct {
    ALLEGRO_COLOR cor;
    int tempo_de_cpu;
    int tempo_de_IO;
    int quant_rodadas;
    bool ativo;
    int tempo_cpu_const;
    int tempo_io_const;
    int tempo_espera;       
    int ultima_vez_visto;    
} Processo;

typedef struct No {
    Processo processo;
    struct No *prox_no;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

void inserir_fila(Fila *fila, Processo p, int *cont);
Processo remover_fila(Fila *fila, int *cont);
int isempty(Fila *fila);
No *pegar_inicio(Fila *fila);
