#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>

using namespace std;

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

int main(){
    int c, n;
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
            }
        }
        printMatrix(matriz_ady);
    }
    return 0;
}

/*
matriz de ady para floyd, con l(u,v) funcion de peso
         { 0         si i=j
l(i,j) = { l(u,v)    si (u,v) esta en E
         { inf       si (u,v) NO esta en E
*/