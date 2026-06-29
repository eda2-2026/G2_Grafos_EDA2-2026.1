#ifndef bomba_h
#define bomba_h

#include <stdlib.h>
#include <time.h>


typedef struct {
    int bombs;      // número de bombas ao redor
    int boolean;    // booleana = 0 -> não é bomba, booleana = 1 -> é bomba
    int flag;       // 0 -> não marcada, 1 -> aberta, -1 -> marcada com bandeira
} casa;

typedef struct {
    int linha;
    int coluna;
} Vertice;

typedef struct {
    Vertice origem;
    Vertice destino;
} Aresta;

typedef struct {
    Vertice dados[400];
    int inicio;
    int fim;
} Fila;

typedef struct {
    int tamanho;
    Vertice passos[400];
} Rota;

int vertice_valido(int MAX, Vertice vertice);
int obter_arestas_do_vertice(int MAX, Vertice origem, Aresta arestas[8]);

void gerar_bombas(int max, casa matrix[max][max], int num_bombas);
void contador_bombs(int MAX, casa matrix[MAX][MAX]);

void printa_ou_n(int MAX, casa matrix[MAX][MAX], int pi, int pj);
int vitoria(int MAX, casa matrix[MAX][MAX], int num_bombas);

void inicializar_fila(Fila *f);
void enfileirar(Fila *f, Vertice v);
Vertice desenfileirar(Fila *f);
int fila_vazia(Fila *f);

int buscar_X_caminhos_dijkstra(int MAX, casa matrix[MAX][MAX], Vertice inicio, int qtd_desejada, Rota rotas_encontradas[]);
#endif