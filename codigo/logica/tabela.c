#include "tabela.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>

Tabela teste = {
    .n_colunas = 3,
    .n_linhas = 10, // Variável

    .titulos = {"Processo", "CPU", "Disco"},

    .linhas = {
        {"01", "30%", "0.1 Mbps"},
        {"02", "10%", "50 Mbps"},
        {"03", "01%", "0 Mbps"},
    }
};