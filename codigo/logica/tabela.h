#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define MAX_COLUNAS 3
#define MAX_LINHAS 5

typedef struct {
    int n_colunas;
    int n_linhas;

    char titulos[MAX_COLUNAS][30];
    char linhas[MAX_LINHAS][MAX_COLUNAS][30];
} Tabela;
