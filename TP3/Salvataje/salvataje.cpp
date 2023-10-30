#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <tuple>
#include <limits.h>

using namespace std;

// fortaleza: N salones divididos por murallas
// Escalar muralla   -> 1 min
// Recorrer pasadizo -> 2 min
// Maximos pasadizos que se pueden recorrer por caso: 3
// No se puede ir hacia salones anteriores
// No se puede entrar a un pasadizo desde su salida

// Entrar al primer salon tambien tarda 1 minuto !!!!!


int cant_salones;

void printMatrix(vector<vector<int>> &grafo){
    for(vector<int> i : grafo){
        cout << "(";
        for(int l = 0; l < i.size(); l++)
            cout << i[l] << " ";
        cout << ")" << endl;
    }
}

void printVector(vector<int> &v){
    for(int i : v)
        cout << v[i] << " ";
    cout << endl;
}

int distanciaMinima(vector<int> dist, vector<bool> spt){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < cant_salones; v++)
        if (spt[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}


void dijkstra(vector<vector<int>> &grafo, int src){
    vector<int> dist(cant_salones, INT_MAX);    //dist guarda la distancia mas corta del origen hasta i
    vector<bool> spt(cant_salones, false);     //spt es true sii el nodo i esta incluido en shortest path tree o si ya se sabe la menor distancia del origen a i
 
    dist[src] = 0;
 
    for (int count = 0; count < cant_salones - 1; count++) {
        int u = distanciaMinima(dist, spt);

        spt[u] = true;
        for (int v = 0; v < cant_salones; v++)
            if (!spt[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }
    printVector(dist);
    //int N = dist.size();
    cout << dist[dist.size()-1] + 1 << endl; // sumo 1 a la respuesta pq hay que considerar que entrar al primer salon (1er nodo) tambien tarda 1 min
    //printSolution(dist, cant_salones);
}



int main(){
    int c, cant_tuneles;
    cin >> c;

    for(int i = 0; i < c; i++){
        cin >> cant_salones >> cant_tuneles;
        vector<vector<int>> grafo(cant_salones, vector<int>(cant_salones,0));

        for(int k = 0; k < cant_salones; k++){
            if(k == cant_salones-1)
                continue;
            else
                grafo[k][k+1] = 1;  // cada nodo (salon) tiene una arista dirigida al siguiente nodo con peso 1 (pq tarda 1 min en saltar la muralla)
            
        }


        for(int j = 0; j < cant_tuneles; j++){
            int inicio, fin;
            cin >> inicio >> fin;

            grafo[inicio-1][fin-1] = 2;  // resto 1 en inicio y fin pq vectores empiezan con 0 y los casos de test empiezan en 1
                                         // le asigno 2 a la arista pq tarda 2 min en atravezar el tunel
        }


        //printMatrix(grafo);
        dijkstra(grafo, 0);
        
    }

    return 0;
}
