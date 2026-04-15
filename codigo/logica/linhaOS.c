#include "linhaOS.h"
#include "fila.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>

void desenhar_linha_de_execucao(Globais *os, ALLEGRO_FONT *fonte) {
    // Processos: Exec e IO
    // Exec
    for (int i = 0; i < os->total_exec - 1; i++) {
        float y_base = (ALTURA / 2) + (ALTURA / 4) - 75;

        al_draw_filled_rectangle(
            os->grad_exec[i].x0,
            y_base - 15,
            os->grad_exec[i].x1,
            y_base + 15,
            os->grad_exec[i].cor
        );

        al_draw_rectangle(
            os->grad_exec[i].x0,
            y_base - 15,
            os->grad_exec[i].x1,
            y_base + 15,
            al_map_rgb(0, 0, 0),
            1
        );
    }
    // IO
    for (int i = 0; i < os->total_IO - 1; i++) {
        float y_base = (ALTURA / 2) + (ALTURA / 4) + 75;

        al_draw_filled_rectangle(
            os->grad_io[i].x0,
            y_base - 15,
            os->grad_io[i].x1,
            y_base + 15,
            os->grad_io[i].cor
        );

        al_draw_rectangle(
            os->grad_io[i].x0,
            y_base - 15,
            os->grad_io[i].x1,
            y_base + 15,
            al_map_rgb(0, 0, 0),
            1
        );
    }
}

void exec(Globais *os) {
    /*
        Coração do programa, simulador do gerênciamento de processos pelo SO
    */
    // Variaveis temporarias só para poupar texto
    float larg = 30;

    int quantum = os->so_info.quantum;
    Processo finalizado;

    // Loop principal do programa
    if (os->so_info.tempo_total > 0) {

        if (!isempty(&os->so_info.fila_exec)) {
            No *atual = pegar_inicio(&os->so_info.fila_exec);

            int k = os->total_exec;
            os->grad_exec[k].fila = 0;
            os->grad_exec[k].cor = atual->processo.cor;
            os->grad_exec[k].x0 = os->larg_x_exec;
            os->grad_exec[k].x1 = os->larg_x_exec + larg;

            os->larg_x_exec += larg;
            os->total_exec++;

            if (atual->processo.tempo_de_cpu == 0 ||
                atual->processo.quant_rodadas == 0) {
                atual->processo.ativo = false;
                finalizado = remover_fila(&os->so_info.fila_exec);
                if (atual->processo.tempo_de_IO != 0) {
                    os->larg_x_IO = os->larg_x_exec - 10;
                    inserir_fila(&os->so_info.fila_IO, finalizado);
                }
            } else if (atual->processo.tempo_de_cpu - quantum < 0) {
                if (atual->prox_no != NULL) {
                    atual->processo.ativo = false;
                    atual->prox_no->processo.tempo_de_cpu +=
                        atual->processo.tempo_de_cpu - quantum;
                }
                finalizado = remover_fila(&os->so_info.fila_exec);
                if (atual->processo.tempo_de_IO != 0) {
                    os->larg_x_IO = os->larg_x_exec - 10;
                    inserir_fila(&os->so_info.fila_IO, finalizado);
                }
            } else {
                atual->processo.tempo_de_cpu -= quantum;
                atual->processo.quant_rodadas--;
            }
        }

        if (!isempty(&os->so_info.fila_IO)) {

            No *atual_io = pegar_inicio(&os->so_info.fila_IO);

            int j = os->total_IO;
            os->grad_io[j].fila = 1;
            os->grad_io[j].cor = atual_io->processo.cor;
            os->grad_io[j].x0 = os->larg_x_IO;
            os->grad_io[j].x1 = os->larg_x_IO + larg;

            os->larg_x_IO += larg;
            os->total_IO++;

            if (atual_io->processo.tempo_de_IO == 0) {
                atual_io->processo.ativo = false;
                remover_fila(&os->so_info.fila_IO);
            } else if (atual_io->processo.tempo_de_IO - quantum < 0) {
                if (atual_io->prox_no != NULL) {
                    atual_io->processo.ativo = false;
                    atual_io->prox_no->processo.tempo_de_cpu +=
                        atual_io->processo.tempo_de_cpu - quantum;
                }
                atual_io->processo.ativo = false;
                remover_fila(&os->so_info.fila_IO);
            } else {
                atual_io->processo.tempo_de_IO -= quantum;
                atual_io->processo.quant_rodadas--;
            }
        }
        os->so_info.tempo_total -= quantum;
    }
}

void carregar_fila(Globais *os) {
    for (int i = 0; i < os->q_processos; i++) {
        inserir_fila(&os->so_info.fila_exec, os->processos[i]);
    }
}
