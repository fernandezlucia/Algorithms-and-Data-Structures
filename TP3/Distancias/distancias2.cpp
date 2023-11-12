#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>

using namespace std;

#define INF INT_MAX

int n;
vector<vector<int>> aristas;
vector<vector<int>> adj_original;
bool imposible;

// DIST DE CONEXION(u,v) = minima cant. de enlaces para ir de u a v
// LATENCIA(u,v) = minima cant. de tiempo (en milisegundos > 0) que se tarde en ir de u a v

// Hay q obtener la dist. de conexion entre todo nodo (u,v) sabiendo las latencias o si las latencias son incompatibles con la red
// Dan la matriz de adyacencias con peso, hay q devolver la matriz de distancias? -> Algo floyd?

void printSolution(vector<vector<int>> &matriz_dist){
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matriz_dist[i][j] == INF)
				cout << "INF"
					<< " ";
			else
				cout << matriz_dist[i][j] << " ";
		}
		cout << endl;
	}
}

void floydWarshall(vector<vector<int>> &dist){
	int i, j, k;
    
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if ((dist[k][j] != INF && dist[i][k] != INF) && dist[i][j] > (dist[i][k] + dist[k][j])){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
                else if ((dist[k][j] != INF && dist[i][k] != INF) && dist[i][j] == (dist[i][k] + dist[k][j])){
                    aristas[i][j] = aristas[i][k] + aristas[k][j];
                }
			}
		}
	}

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i!=j && (dist[i][j] < adj_original[i][j] && adj_original[i][j] != 0)){
                cout << "IMPOSIBLE" << endl;
                imposible = true;
                return;
            }
        }
    }
}


int main(){
    int c;
    cin >> c;

    for(int k = 0; k < c; k++){
        cin >> n;
        vector<vector<int>> matriz_ady(n, vector<int>(n,0));
        aristas = vector<vector<int>>(n, vector<int>(n, 0));
        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < i+1; j++){
                int temp;
                cin >> temp;
                matriz_ady[i+1][j] = temp;
                matriz_ady[j][i+1] = temp;
                aristas[i+1][j] = 1;
                aristas[j][i+1] = 1;
            }
        }
        imposible = false;
        adj_original = matriz_ady;
        floydWarshall(matriz_ady);

        if(!imposible){
            cout << "POSIBLE" << endl;
            printSolution(aristas);
        }
    }
    return 0;
}
