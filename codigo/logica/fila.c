#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <stdlib.h>
#include "fila.h"


void inserir_fila(Fila *fila, Processo p, int *cont) {
    No * novo_no = (No*)malloc(sizeof(No));
    novo_no->processo = p;
    novo_no->prox_no = NULL;
    (*cont)++;   
    if(isempty(fila)) {
        fila->fim = novo_no;
        fila->inicio = novo_no;
    } else {
        fila->fim->prox_no = novo_no;
        fila->fim = novo_no;
    }
}
Processo remover_fila(Fila *fila, int *cont) {
    if(isempty(fila)) {
        Processo vazio = {0};
        return vazio; 
    } else {
        (*cont)--;
        if(fila->inicio->prox_no == NULL) {
            No * temp = fila->inicio;
            Processo p = temp->processo;
            fila->inicio = NULL;
            fila->fim = NULL;
            free(temp);
            return p;
        }
        else {
            No * temp = fila->inicio;
            fila->inicio = fila->inicio->prox_no;
            Processo p = temp->processo;
            free(temp);
            return p;
        }
    }
}

int isempty(Fila * fila) {
    if(fila->inicio == NULL) {
        return 1;
    }
    return 0;
}

No *pegar_inicio(Fila *fila) {
    if(!isempty(fila)) {
        return fila->inicio;
    }
    return NULL;
}