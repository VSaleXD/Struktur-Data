#include<bits/stdc++.h>
using namespace std;

#define Maks_verteks 100

typedef struct{
    int n_vertex;
    int n_edge;
    int adj_matrix[Maks_verteks][Maks_verteks];
    bool has_cycle = 0;
} Graph;

typedef enum {WHITE, GRAY, BLACK} COLOR;
#define inf 1000000000
int finish_time[Maks_verteks];
int timer = 0;

class graf{
    public:
        Graph G;
        void inisialisasi_graph(int n_vertex, int n_edge){
            G.n_vertex = n_vertex;
            G.n_edge = n_edge;
            for(int i=0; i<Maks_verteks; i++){
                for(int j=0; j<Maks_verteks; j++){
                    if(i < n_vertex && j < n_vertex){
                        G.adj_matrix[i][j] = 0; 
                    } else {
                        G.adj_matrix[i][j] = -1; 
                    }
                } 
            } 
        } 

        void print_graph(){
            // for (int i = 0; i < G.n_vertex; i++){
            //     cout << "\t" << i;
            // } cout<< endl;
            for(int i=0; i<G.n_vertex; i++){
                // cout << i << "\t";
                for(int j=0; j<G.n_vertex; j++){
                    cout << G.adj_matrix[i][j] << " ";
                }
                cout << endl;
            }
        }

        void dfs_visit(int vertex, COLOR color[]){
            cout << vertex << " ";
            cout << "time: " << timer << endl;
            timer++; 
            color[vertex] = GRAY; 

            for(int i=0; i<G.n_vertex; i++){
                if(G.adj_matrix[vertex][i] == 1 && color[i] != WHITE){ //soal 1 2
                   if(color[i] == GRAY){
                        // cout << "Cycle" << endl;
                        G.has_cycle = 1; // soal 3 
                    }
                }
                if(G.adj_matrix[vertex][i] == 1 && color[i] == WHITE){
                    dfs_visit(i, color);
                }
            }
            color[vertex] = BLACK;
            timer++;
            finish_time[vertex] = timer;
        } 

        int dfs(){
            COLOR color[Maks_verteks];
            for(int i=0; i<G.n_vertex; i++){
                color[i] = WHITE;
                finish_time[i] = inf; // soal 4
            }
            for(int i=0; i<G.n_vertex; i++){
                if(color[i] == WHITE){
                    dfs_visit(i, color);
                }
            }

            return G.has_cycle;
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
        g.G.adj_matrix[u][v] = 1; 
        // g.G.adj_matrix[v][u] = 1;
    }
    g.print_graph();


    int has_cycle = g.dfs();
    for(int i=0; i<n_v; i++){
        cout << "Finish time vertex " << i << ": " << finish_time[i] << endl;
    }


    if(has_cycle){ // soal 5 6 7
        cout << "Cycle" << endl;
    }else{
        int vertices[n_v];
        for(int i = 0; i < n_v; i++) {
            vertices[i] = i;
        }
        
        qsort(vertices, n_v, sizeof(int), [](const void* a, const void* b) {
            int idx_a = *(int*)a;
            int idx_b = *(int*)b;
            return finish_time[idx_b] - finish_time[idx_a]; // descending
        });
        
        cout << "Topological Sort: ";
        for(int i = 0; i < n_v; i++) {
            cout << vertices[i] << " ";
        }
        cout << endl;
    }

    return 0;
}

// 8 9 0 1 1 3 3 2 2 1 3 4 4 5 5 7 7 6 6 4

 
// Test case 1: DAG (Directed Acyclic Graph)
// 6 6 5 2 5 0 4 0 4 1 2 3 3 1
// Test case 2: Graf linear
// 5 4 0 1 1 2 2 3 3 4
// Test case 3: Graf tidak terhubung
// 6 4 0 1 1 2 3 4 4 5
// Test Case 4: Graf Kompleks
// 7 8 0 1 0 2 1 3 1 4 2 4 2 5 3 6 4 6