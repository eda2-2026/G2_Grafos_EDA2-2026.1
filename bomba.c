#include "bomba.h"
#include <stdlib.h>

static const int DIRECOES_ARESTAS[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    { 0, -1},          { 0, 1},
    { 1, -1}, { 1, 0}, { 1, 1}
};

static const int DIRECOES_ORTOGONAIS[4][2] = {
    {-1, 0}, { 0, -1},{ 0, 1},{ 1, 0}
};

int obter_arestas_ortogonais(int MAX, Vertice origem, Aresta arestas[4]) {
    int total_arestas = 0;
    for (int i = 0; i < 4; i++) {
        Vertice destino = {
            origem.linha + DIRECOES_ORTOGONAIS[i][0],
            origem.coluna + DIRECOES_ORTOGONAIS[i][1]
        };
        if (destino.linha >= 0 && destino.linha < MAX && destino.coluna >= 0 && destino.coluna < MAX) {
            arestas[total_arestas].origem = origem;
            arestas[total_arestas].destino = destino;
            total_arestas++;
        }
    }
    return total_arestas;
}

int vertice_valido(int MAX, Vertice vertice) {
    return vertice.linha >= 0 && vertice.linha < MAX &&
           vertice.coluna >= 0 && vertice.coluna < MAX;
}

int obter_arestas_do_vertice(int MAX, Vertice origem, Aresta arestas[8]) {
    int total_arestas = 0;
    for (int i = 0; i < 8; i++) {
        Vertice destino = {
            origem.linha + DIRECOES_ARESTAS[i][0],
            origem.coluna + DIRECOES_ARESTAS[i][1]
        };
        if (vertice_valido(MAX, destino)) {
            arestas[total_arestas].origem = origem;
            arestas[total_arestas].destino = destino;
            total_arestas++;
        }
    }
    return total_arestas;
}

void gerar_bombas(int max, casa matrix[max][max], int num_bombas) {
    int bombas_colocadas = 0;
    while (bombas_colocadas < num_bombas) {
        int i = rand() % max;
        int j = rand() % max;
        if (matrix[i][j].boolean == 0) {
            matrix[i][j].boolean = 1;
            bombas_colocadas++;
        }
    }
}

void contador_bombs(int MAX, casa matrix[MAX][MAX]) {
    for (int pi = 0; pi < MAX; pi++) {
        for (int pj = 0; pj < MAX; pj++) {
            Vertice vertice_atual = {pi, pj};
            Aresta arestas[8];
            int total_arestas = obter_arestas_do_vertice(MAX, vertice_atual, arestas);
            matrix[pi][pj].bombs = 0;
            for (int i = 0; i < total_arestas; i++) {
                Vertice vizinho = arestas[i].destino;
                if (matrix[vizinho.linha][vizinho.coluna].boolean == 1) {
                    matrix[pi][pj].bombs++;
                }
            }
        }
    }
}

void printa_ou_n(int MAX, casa matrix[MAX][MAX], int pi, int pj){
    Vertice vertice_atual = {pi, pj};
    Aresta arestas[8];
    int total_arestas = obter_arestas_do_vertice(MAX, vertice_atual, arestas);

    if (matrix[pi][pj].flag != 0) return;
    matrix[pi][pj].flag = 1;

    for (int i = 0; i < total_arestas; i++) {
        Vertice vizinho = arestas[i].destino;
        if (matrix[vizinho.linha][vizinho.coluna].bombs == 0) {
            printa_ou_n(MAX, matrix, vizinho.linha, vizinho.coluna);
        } else {
            matrix[vizinho.linha][vizinho.coluna].flag = 1;
        }
    }
}

int vitoria(int MAX, casa matrix[MAX][MAX], int num_bombas){
    int casas_abertas = 0;
    int bandeira_certa = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (matrix[i][j].flag == 1) casas_abertas++;
            if (matrix[i][j].flag == -1 && matrix[i][j].boolean == 1) bandeira_certa++;
        }
    }
    if (casas_abertas == MAX * MAX - num_bombas || bandeira_certa == num_bombas) return 1;
    return 0;
}
typedef struct {
    int linha;
    int coluna;
    int custo_acumulado;
    int direcao_chegada; 
} NoDijkstra;

typedef struct {
    NoDijkstra dados[4000];
    int tamanho;
} FilaPrioridade;

void inicializar_fp(FilaPrioridade *fp) {
    fp->tamanho = 0;
}

void inserir_fp(FilaPrioridade *fp, NoDijkstra no) {
    fp->dados[fp->tamanho] = no;
    fp->tamanho++;
}

NoDijkstra extrair_min_fp(FilaPrioridade *fp) {
    int idx_min = 0;
    for (int i = 1; i < fp->tamanho; i++) {
        if (fp->dados[i].custo_acumulado < fp->dados[idx_min].custo_acumulado) {
            idx_min = i;
        }
    }
    NoDijkstra menor = fp->dados[idx_min];
    fp->dados[idx_min] = fp->dados[fp->tamanho - 1];
    fp->tamanho--;
    return menor;
}

int fp_vazia(FilaPrioridade *fp) {
    return fp->tamanho == 0;
}

// ALGORITMO DE DIJKSTRA (peso maior nas curvas)
int buscar_X_caminhos_dijkstra(int MAX, casa matrix[MAX][MAX], Vertice inicio, int qtd_desejada, Rota rotas_encontradas[]) {
    FilaPrioridade fp;
    inicializar_fp(&fp);

    int custo_menor[MAX][MAX];
    Vertice origem[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            custo_menor[i][j] = 999999; 
            origem[i][j] = (Vertice){-1, -1};
        }
    }

    NoDijkstra inicio_no = {inicio.linha, inicio.coluna, 0, -1};
    inserir_fp(&fp, inicio_no);
    custo_menor[inicio.linha][inicio.coluna] = 0;

    int bombas_achadas = 0;
    Vertice bombas_destino[10]; 

    while (!fp_vazia(&fp)) {
        NoDijkstra atual = extrair_min_fp(&fp);
        if (atual.custo_acumulado > custo_menor[atual.linha][atual.coluna]) {
            continue;
        }

        Vertice v_atual = {atual.linha, atual.coluna};

        // Achou uma bomba
        if (matrix[atual.linha][atual.coluna].boolean == 1) {
            int ja_achou = 0;
            for(int k=0; k < bombas_achadas; k++) {
                if(bombas_destino[k].linha == atual.linha && bombas_destino[k].coluna == atual.coluna) ja_achou = 1;
            }
            if(!ja_achou) {
                bombas_destino[bombas_achadas] = v_atual;
                bombas_achadas++;
                if (bombas_achadas == qtd_desejada) break; 
            }
            continue; 
        }
        for (int d = 0; d < 4; d++) {
            Vertice vizinho = {
                atual.linha + DIRECOES_ORTOGONAIS[d][0],
                atual.coluna + DIRECOES_ORTOGONAIS[d][1]
            };
            
            if (vertice_valido(MAX, vizinho)) {
                int novo_custo = atual.custo_acumulado + 10; 

                if (atual.direcao_chegada != -1 && atual.direcao_chegada != d) {
                    novo_custo += 1; 
                }

                if (novo_custo < custo_menor[vizinho.linha][vizinho.coluna]) {
                    custo_menor[vizinho.linha][vizinho.coluna] = novo_custo;
                    origem[vizinho.linha][vizinho.coluna] = v_atual;
                    
                    if (fp.tamanho < 3999) {
                        NoDijkstra vizinho_no = {vizinho.linha, vizinho.coluna, novo_custo, d};
                        inserir_fp(&fp, vizinho_no);
                    }
                }
            }
        }
    }
    
    // Constrói as rotas fazendo o caminho reverso
    for (int b = 0; b < bombas_achadas; b++) {
        int tamanho_caminho = 0;
        Vertice passo = bombas_destino[b];

        while (passo.linha != inicio.linha || passo.coluna != inicio.coluna) {
            rotas_encontradas[b].passos[tamanho_caminho] = passo;
            tamanho_caminho++;
            passo = origem[passo.linha][passo.coluna];
        }
        rotas_encontradas[b].passos[tamanho_caminho] = inicio;
        tamanho_caminho++;

        // Inverte a ordem
        for (int i = 0; i < tamanho_caminho / 2; i++) {
            Vertice temp = rotas_encontradas[b].passos[i];
            rotas_encontradas[b].passos[i] = rotas_encontradas[b].passos[tamanho_caminho - 1 - i];
            rotas_encontradas[b].passos[tamanho_caminho - 1 - i] = temp;
        }
        rotas_encontradas[b].tamanho = tamanho_caminho;
    }

    return bombas_achadas; 
}