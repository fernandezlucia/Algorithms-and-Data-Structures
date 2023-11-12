#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>
#include <queue>

using namespace std;

int N;
int INF = INT_MAX;
vector<vector<int>> capacidad;
vector<vector<int>> grafo;

struct segmento{
    int id;
    bool tipo;  // 0 fila, 1 columna
    pair<int, int> inicio;
    pair<int, int> fin;
};
vector<segmento> filas;
vector<segmento> columnas;

void printMatrix(vector<vector<int>> &matriz){
    for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[i].size() ; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
}

void printSeg(vector<segmento> &v){

    for(segmento a : v){     
        cout << "(" << a.id << ", " << a.tipo << " " << "<" << a.inicio.first << ", " << a.inicio.second << ">" << " " << "<" << a.fin.first << ", " << a.fin.second << ">" << ")" << endl;
    }
    
}

void printSeg2(vector<segmento> &v){
    for(segmento a : v){     
        cout << "(" << a.id << "), ";
    }
}

void printGrafo(vector<vector<segmento>> &matriz){
    for (int i = 0; i < matriz.size(); i++) {
        cout << "i: " << i << " ";
		printSeg2(matriz[i]);
		cout << endl;
	}
}

vector<segmento> extraerFilas(vector<vector<int>>& tablero, int &id){
    vector<segmento> filas(0);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            pair<int, int> inicio = {i, j};
            pair<int, int> fin = {i, j};

            if(tablero[i][j] == 1)
                continue;

            while(tablero[i][j] != 1 && j != N-1){
                j++;
                fin = {i, j};
            }
            
            j = fin.second;
            
            if(tablero[i][j] == 1)
                fin = {i, j-1};
            
            segmento v = {id, 0, inicio, fin};
            filas.push_back(v);
            id++;
        }
    }
    return filas;
}

vector<segmento> extraerColumnas(vector<vector<int>>& tablero, int& id){
    vector<segmento> columnas(0);
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++){
            pair<int, int> inicio = {i, j};
            pair<int, int> fin = {i, j};

            if(tablero[i][j] == 1)
                continue;
                
            while(tablero[i][j] != 1 && i != N-1){
                i++;
                fin = {i, j};
            }
            i = fin.first;
            
            if(tablero[i][j] == 1 && i != 0)
                fin = {i-1, j};
            
            segmento v = {id, 1, inicio, fin};
            columnas.push_back(v);
            id++;
        }
    }
    return columnas;
}

bool puntoPertenece(segmento s, pair<int, int> p){
    return (s.inicio.first <= p.first && p.first <= s.fin.first) && (s.inicio.second <= p.second && p.second <= s.fin.second);
}

bool hayInterseccion(segmento fila, segmento columna){
    int x = fila.inicio.first;             
    int y = columna.inicio.second;
    
    return puntoPertenece(fila, {x, y}) && puntoPertenece(columna, {x, y});
}

vector<vector<int>> procesarTablero(vector<vector<int>>& tablero){
    vector<vector<segmento>> grafo_seg;
    vector<vector<int>> grafo;
    int id = 1;
    filas = extraerFilas(tablero, id);
    columnas = extraerColumnas(tablero, id);

    grafo.push_back({});

    for(segmento f : filas){
        grafo_seg.push_back({});
        grafo[0].push_back(f.id);
        grafo.push_back({});
        for(segmento c : columnas){            
            if(hayInterseccion(f,c)){
                grafo_seg.back().push_back(c);
                grafo.back().push_back(c.id);
            }
        }
    }

    grafo.push_back({});
    for(segmento c : columnas){
        grafo.back().push_back(c.id);
    }
    
    //cout << "filas: " << endl;   
    //printSeg(filas);
    //cout << "columnas: " << endl;
    //printSeg(columnas);
//
    //printGrafo(grafo_seg);
    printMatrix(grafo);
    return grafo;
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : grafo[cur]) {
            if (parent[next] == -1 && capacidad[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidad[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(filas.size() + columnas.size());
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidad[prev][cur] -= new_flow;
            capacidad[cur][prev] +=  new_flow;
            cur = prev;
        }
    }

    return flow;
}



int main(){
    int c;
    cin >> c;

    for(int i = 0; i < c; i++){
        cin >> N;
        vector<vector<int>> tablero(N, vector<int>(N, 0));

        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                int casillero_roto;
                cin >> casillero_roto;
                tablero[j][k] = casillero_roto;
            }
        }

        grafo = procesarTablero(tablero);
        int n = filas.size()+columnas.size();
        capacidad = (vector<vector<int>>(n, vector<int>(n, 1)));
        int res = maxflow(0, n);
        cout << res << endl;

    }

    return 0;
}