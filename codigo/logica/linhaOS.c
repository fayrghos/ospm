#include "linhaOS.h"
#include "../cores.h"
#include "fila.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>

int aux = 0;
int tempo = 0;
int salva = 0;

void desenhar_linha_de_execucao(Globais *os, ALLEGRO_FONT *fonte) {
    // Processos: Exec e IO
    // Exec
    static int flip = 0;
    if (!flip) {
        for (int i = 0; i < os->total_exec; i++) {
            float y_base = (ALTURA / 2) + (ALTURA / 4) - 75;

            if (i % 2 == 0) {
                al_draw_textf(
                    fonte,
                    COR_BRANCO,
                    os->grad_exec[i].x1,
                    y_base - 50,
                    0,
                    " t: %d ",
                    os->grad_exec[i].tempo_processo
                );
            } else {
                al_draw_textf(
                    fonte,
                    COR_BRANCO,
                    os->grad_exec[i].x1,
                    y_base + 50,
                    0,
                    " t: %d ",
                    os->grad_exec[i].tempo_processo
                );
            }

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
                COR_PRETO,
                1
            );
            if (os->grad_exec[i].x1 >= LARGURA - 110) {
                flip = 1;
                continue;
            }
        }
        // IO
        for (int i = 0; i < os->total_IO; i++) {
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
                COR_PRETO,
                1
            );

            if (os->grad_io[i].x1 >= LARGURA - 90) {
                flip = 1;
                continue;
            }
        }

    } else {
        os->total_exec = 0;
        os->total_IO = 0;
        // Ponto inicial na esquerda
        aux = 0;
        os->larg_x_IO = 0;
        os->larg_x_exec = 90;
        flip = 0;
    }
}

void exec(Globais *os) {
    /*
        Coração do programa, simulador do gerênciamento de processos pelo SO
    */
    // Variaveis temporarias só para poupar texto

    int quantum = os->so_info.quantum;
    Processo finalizado;
    Processo saida;

    // Loop principal do programa
    if (os->so_info.tempo_total > 0) {

        if (!isempty(&os->so_info.fila_exec)) {
            int tempo_gasto = quantum;

            No *atual = pegar_inicio(&os->so_info.fila_exec);

            if (atual->processo.tempo_de_cpu < quantum &&
                atual->processo.tempo_de_cpu > 0) {
                tempo_gasto = atual->processo.tempo_de_cpu;
            }

            int margem = 90;
            int k = os->total_exec;
            os->grad_exec[k].fila = 0;
            os->grad_exec[k].cor = atual->processo.cor;
            os->grad_exec[k].tempo_processo = tempo * quantum;
            if(k == 0) {
                os->grad_exec[k].x0 = margem;
            }else {
                os->grad_exec[k].x0 = os->grad_exec[k-1].x1 + 5;
            }

            float larg_final = ((float)tempo_gasto/quantum) * os->escala;
            os->grad_exec[k].x1 = os->grad_exec[k].x0 + larg_final;

            os->total_exec++;
            

            atual->processo.tempo_de_cpu -= tempo_gasto;

            if (atual->processo.tempo_de_cpu <= 0) {
                atual->processo.ativo = false;
                finalizado = remover_fila(&os->so_info.fila_exec, &os->total_exec_analise);
                

                if (finalizado.tempo_de_IO > 0) {
                    inserir_fila(&os->so_info.fila_IO, finalizado, &os->total_io_analise);
                } else if (finalizado.quant_rodadas > 1) {
                    finalizado.quant_rodadas--;
                    finalizado.tempo_de_cpu = finalizado.tempo_cpu_const;
                    inserir_fila(&os->so_info.fila_exec, finalizado, &os->total_exec_analise);
                }

            } else if (atual->processo.tempo_de_cpu > 0) {
                saida = remover_fila(&os->so_info.fila_exec, &os->total_exec_analise);
                inserir_fila(&os->so_info.fila_exec, saida, &os->total_exec_analise);
            }
        }

        if (!isempty(&os->so_info.fila_IO)) {

            No *atual_io = pegar_inicio(&os->so_info.fila_IO);

            int tempo_gasto = quantum;

            if (atual_io->processo.tempo_de_IO < quantum &&
                atual_io->processo.tempo_de_IO > 0) {
                tempo_gasto = atual_io->processo.tempo_de_IO;
            }

            int j = os->total_IO;
            int k = os->total_exec;
            int margem = 90;
            os->grad_io[j].fila = 1;
            os->grad_io[j].cor = atual_io->processo.cor;
            os->grad_io[j].tempo_processo = tempo * quantum;

            if(j == 0) {
                if(k > 0) os->grad_io[j].x0 = os->grad_exec[k-1].x1;
                else os->grad_io[j].x0 = 90;
            }else {
                os->grad_io[j].x0 = os->grad_io[j-1].x1 + 5;
            }

            float larg_final = ((float)tempo_gasto/quantum) * os->escala;
            os->grad_io[j].x1 = os->grad_io[j].x0 + larg_final;

            os->total_IO++;

            atual_io->processo.tempo_de_IO -= tempo_gasto;

            if (atual_io->processo.tempo_de_IO <= 0) {
                finalizado = remover_fila(&os->so_info.fila_IO, &os->total_io_analise);
    
                finalizado.quant_rodadas--;

                if (finalizado.quant_rodadas > 0) {
                    finalizado.tempo_de_cpu = finalizado.tempo_cpu_const;
                    finalizado.tempo_de_IO = finalizado.tempo_io_const;
                    
                    inserir_fila(&os->so_info.fila_exec, finalizado ,&os->total_exec_analise);
                }
                
            }
        }
        aux++;
        tempo++;
        os->so_info.tempo_total -= quantum;
    }
}

void carregar_fila(Globais *os) {
    for (int i = 0; i < os->q_processos; i++) {
        inserir_fila(&os->so_info.fila_exec, os->processos[i], &os->total_exec_analise);
    }
}

