#include "linhaOS.h"
#include "../cores.h"
#include "fila.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include "heap.h"

int maior_heap(int atual, Processo esq, Processo dir) {
    if(esq.prioridade > dir.prioridade) return 2*atual+1;
    return 2*atual+2;
}

void balancea_heap(Processo v[], int i, int f) {
    if(i < f) {
        int esq = 2*i+1;
        int dir = 2*i+2;
        int atual = i;
        int m = 0;
        int ind_maior = 0;
        Processo temp;

        if(esq < f && dir < f) {
            m = 1;
        }
        else if(esq < f) {
            m = 0;
        }        

        if(m) {
           ind_maior = maior_heap(atual, v[esq], v[dir]);
            if(ind_maior < f && v[atual].prioridade < v[ind_maior].prioridade) {
                temp = v[atual];
                v[atual] = v[ind_maior];
                v[ind_maior] = temp;
                atual = ind_maior; 
                m = 2;
            }
        } 
        else {
            if(esq < f && v[atual].prioridade < v[esq].prioridade) {
                temp = v[atual];
                v[atual] = v[esq];
                v[esq] = temp;
                atual = esq;
                m = 2; 
            }
        }
        if(m == 2) {
            return balancea_heap(v, atual, f);
        }
        
    }
}

void organiza_heap(Processo *p, int tam) {
    for(int i = (tam/2)-1; i >= 0; i--) {
        balancea_heap(p, i, tam);
    }
    return;
}