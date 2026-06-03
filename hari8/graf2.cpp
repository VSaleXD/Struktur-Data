#include <stdio.h>
#define MAXNUM_VERTICES 100

typedef struct
{
    int n_vertices;
    int n_edges;
    int adjacency_matrix[MAXNUM_VERTICES][MAXNUM_VERTICES];
} Graph;

void inisialisasi_graph(Graph *g, int n_v, int n_e)
{
    int i, j;
    g->n_vertices = n_v;
    g->n_edges = n_e;
    for (i = 0; i < MAXNUM_VERTICES; i++)
    {
        for (j = 0; j < MAXNUM_VERTICES; j++)
        {
            if (i < n_v && j < n_v)
                g->adjacency_matrix[i][j] = 0; // Soal 1
            else
                g->adjacency_matrix[i][j] = -1; // Soal 2
        }
    }
}

void print_adjacency_matrix(Graph *g)
{
    int i, j;
    for (i = 0; i < g->n_vertices; i++)
        printf("\t%d", i);
    printf("\n");
    for (i = 0; i < g->n_vertices; i++)
    {
        printf("%d", i);
        for (j = 0; j < g->n_vertices; j++)
            printf("\t%d", g->adjacency_matrix[i][j]);
        printf("\n");
    }
}

typedef enum
{
    WHITE,
    GRAY,
    BLACK
} COLOR;

void DFS_visit(Graph *g, COLOR *vertex_colors, int v)
{
    int i;
    printf("%d ", v);
    vertex_colors[v] = GRAY;
    for (i = 0; i < g->n_vertices; i++)
    {
        if (g->adjacency_matrix[v][i] == 1 && vertex_colors[i] == WHITE)
            DFS_visit(g, vertex_colors, i);

    }
    vertex_colors[v] = BLACK;
}

void DFS(Graph *g)
{
    COLOR vertex_colors[MAXNUM_VERTICES];
    int i;
    for (i = 0; i < g->n_vertices; i++)
        vertex_colors[i] = WHITE;
    for (i = 0; i < g->n_vertices; i++)
    {
        if (vertex_colors[i] == WHITE)
            DFS_visit(g, vertex_colors, i);
    }
    printf("\n");
}

int main()
{
    int n_v = 0, n_e = 0, i, a, b;
    scanf("%d %d", &n_v, &n_e);
    Graph g;
    inisialisasi_graph(&g, n_v, n_e);
    
    for (i = 0; i < n_e; i++)
    {
        scanf("%d %d", &a, &b);
        g.adjacency_matrix[a][b] = 1; // Soal 3 (directed)
        // Soal 4 (undirected): tambah g.adjacency_matrix[b][a] = 1;
        g.adjacency_matrix[b][a] = 1; 
    }
    print_adjacency_matrix(&g);
    DFS(&g);

    return 0;
}