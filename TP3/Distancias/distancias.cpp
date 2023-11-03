#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>

using namespace std;

#define INF INT_MAX

int n;
// DIST DE CONEXION(u,v) = minima cant. de enlaces para ir de u a v
// LATENCIA(u,v) = minima cant. de tiempo (en milisegundos > 0) que se tarde en ir de u a v

// Hay q obtener la dist. de conexion entre todo nodo (u,v) sabiendo las latencias o si las latencias son incompatibles con la red
// Dan la matriz de adyacencias con peso, hay q devolver la matriz de distancias? -> Algo floyd?

void printMatrix(vector<vector<int>> &grafo){
    for(vector<int> i : grafo){
        cout << "(";
        for(int l = 0; l < i.size(); l++){
            if(l != i.size()-1)
                cout << i[l] << " ";
            else
                cout << i[l];
        }
        cout << ")" << endl;
    }
}

void printVector(vector<int> &v){
    for(int i : v)
        cout << v[i] << " ";
    cout << endl;
}


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


void floyd(vector<vector<int>> &dist){
	int i, j, k;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])	&& (dist[k][j] != INF && dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	printSolution(dist);
}



int main(){
    int c;
    cin >> c;

    for(int k = 0; k < c; k++){
        cin >> n;
        vector<vector<int>> matriz_ady(n, vector<int>(n,0));
        vector<vector<int>> matriz_dist(n, vector<int>(n,0));

        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < i+1; j++){
                int temp;
                cin >> temp;
                matriz_ady[i+1][j] = temp;
                matriz_ady[j][i+1] = temp;
                matriz_dist[i+1][j] = temp;
                matriz_dist[j][i+1] = temp;
            }
        }
        //cout << "llego1" << endl;
        //printMatrix(matriz_ady);
        floyd(matriz_dist);



        if(false){
            cout << "IMPOSIBLE" <<  endl;
        }


        matriz_ady.clear();
        matriz_dist.clear();
    }
    return 0;
}

/*
matriz de ady para floyd, con l(u,v) funcion de peso
         { 0         si i=j
l(i,j) = { l(u,v)    si (u,v) esta en E
         { inf       si (u,v) NO esta en E
*/
