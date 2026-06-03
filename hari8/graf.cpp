#include<bits/stdc++.h>
using namespace std;

#define Maks_verteks 100

typedef struct{
    int n_vertex;
    int n_edge;
    int adj_matrix[Maks_verteks][Maks_verteks];
} Graph;

typedef enum {WHITE, GRAY, BLACK} COLOR;

class graf{
    public:
        Graph G;
        void inisialisasi_graph(int n_vertex, int n_edge){
            G.n_vertex = n_vertex;
            G.n_edge = n_edge;
            for(int i=0; i<Maks_verteks; i++){
                for(int j=0; j<Maks_verteks; j++){
                    if(i < n_vertex && j < n_vertex){
                        G.adj_matrix[i][j] = 0; //soal 1
                    } else {
                        G.adj_matrix[i][j] = -1; // soal 2
                    }
                } 
            } 
        } 

        void print_graph(){
            for (int i = 0; i < G.n_vertex; i++){
                cout << "\t" << i;
            } cout<< endl;
            for(int i=0; i<G.n_vertex; i++){
                cout << i << "\t";
                for(int j=0; j<G.n_vertex; j++){
                    cout << G.adj_matrix[i][j] << "\t";
                }
                cout << endl;
            }
        }

        void dfs_visit(int vertex, COLOR color[]){
            cout << vertex << " ";
            color[vertex] = GRAY;
            for(int i=0; i<G.n_vertex; i++){
                if(G.adj_matrix[vertex][i] == 1 && color[i] == WHITE){
                    dfs_visit(i, color);
                }
            }
            color[vertex] = BLACK;
        } 

        void dfs(){
            COLOR color[Maks_verteks];
            for(int i=0; i<G.n_vertex; i++){
                color[i] = WHITE;
            }
            for(int i=0; i<G.n_vertex; i++){
                if(color[i] == WHITE){
                    dfs_visit(i, color);
                }
            }
        } 
}; 

int main(){
    int n_v = 0, n_e = 0; 
    cin >> n_v >> n_e;

    graf g;
    g.inisialisasi_graph(n_v, n_e);
    for(int i=0; i<n_e; i++){
        int u, v;
        cin >> u >> v;
        g.G.adj_matrix[u][v] = 1; // soal 3 (directed)
        g.G.adj_matrix[v][u] = 1; // soal 4 (undirected)
    }
    g.print_graph();
    cout << "DFS Traversal: ";
    g.dfs(); 

    return 0;
}