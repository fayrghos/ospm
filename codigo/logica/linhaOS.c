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
        //Reset de todo sistema quando o processo bate no limite
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
    
    //Criação de variaveis utilizadas no programa
    int quantum = os->so_info.quantum;
    Processo finalizado;
    Processo saida;

    // Loop principal do programa
    //Enquanto o tempo total informado pelo usuário não for zero ele continua rodando a cada 24 ticks/fps
    if (os->so_info.tempo_total > 0) {

        //Se a fila de execução não for vazia se entra no if
        if (!isempty(&os->so_info.fila_exec)) {
            int tempo_gasto = quantum; //Somente um apelido

            //Pegando o primeiro nó da fila
            No *atual = pegar_inicio(&os->so_info.fila_exec);

            //Se o tempo que o processo precisa para executar é menor que o quantum,
            // se passa o tempo de cpu para o desenho do bloco acompanha e diminuir
            if (atual->processo.tempo_de_cpu < quantum &&
                atual->processo.tempo_de_cpu > 0) {
                tempo_gasto = atual->processo.tempo_de_cpu;
            }

            //Margem do começo do desenho
            int margem = 90;
            //Indica qual o processo da vez para definir os valores pro desenho
            int k = os->total_exec;
            os->grad_exec[k].fila = 0; //não lembro o pq tá aqui 
            os->grad_exec[k].cor = atual->processo.cor;
            os->grad_exec[k].tempo_processo = tempo * quantum; //Definição do tempo para desenho (0, 4 , 8)
            //Tudo em função do quantum

            //Se for o primeiro processo o seu desenho começa no inicio da linha
            if(k == 0) {
                os->grad_exec[k].x0 = margem;
            }else {
            //Caso não seu inicio é no fim do bloco anterior com um espaço de 5
                os->grad_exec[k].x0 = os->grad_exec[k-1].x1 + 5;
            }

            //Cálculo para ter uma largura fixa (Peguei da net)
            float larg_final = ((float)tempo_gasto/quantum) * os->escala;
            os->grad_exec[k].x1 = os->grad_exec[k].x0 + larg_final;

            //Incrementa o total_exec/O indice do processo atual
            os->total_exec++;
            
            //Se gasta o tempo do processo atual para verificação
            atual->processo.tempo_de_cpu -= tempo_gasto;

            //Se o tempo zerou se retira o processo da fila e diminui o total_exec_analise
            if (atual->processo.tempo_de_cpu <= 0) {
                atual->processo.ativo = false;
                finalizado = remover_fila(&os->so_info.fila_exec, &os->total_exec_analise);
                
                //Se ele tiver trabalho de IO é enviado para linha de IO
                if (finalizado.tempo_de_IO > 0) {
                    inserir_fila(&os->so_info.fila_IO, finalizado, &os->total_io_analise);

                } else if (finalizado.quant_rodadas > 1) {
                    //Caso não tenha mais ainda se tem rodada se decrementa a rodada
                    //e reseta o modo de cpu
                    finalizado.quant_rodadas--;
                    finalizado.tempo_de_cpu = finalizado.tempo_cpu_const;
                    inserir_fila(&os->so_info.fila_exec, finalizado, &os->total_exec_analise);
                }

            } else if (atual->processo.tempo_de_cpu > 0) {
                //Caso ainda não tenha zerado se manda para o final da fila e abre espaço para o próximo processo
                saida = remover_fila(&os->so_info.fila_exec, &os->total_exec_analise);
                inserir_fila(&os->so_info.fila_exec, saida, &os->total_exec_analise);
            }
        }

        //Verifica se a fila não é vazia
        if (!isempty(&os->so_info.fila_IO)) {

            //Pega o nó atual
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


            //Msm esquema da linha de exec, porem o x0 tem por base o processo que a chamou
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
                //O processo é removido da fila e a quantidade de rodadas é descontado
                finalizado.quant_rodadas--;

                if (finalizado.quant_rodadas > 0) {
                    //Se ainda não acabou ele retorna a fila de execução e se reseta o tempo de IO
                    finalizado.tempo_de_cpu = finalizado.tempo_cpu_const;
                    finalizado.tempo_de_IO = finalizado.tempo_io_const;
                    inserir_fila(&os->so_info.fila_exec, finalizado ,&os->total_exec_analise);
                }
                
            }
        }
        //Se atualiza umas variaveis para o calculo do tempo
        //e se decrementa o tempo total
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

