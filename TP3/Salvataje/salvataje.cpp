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
// No se puede ir hacia salones anteriores               <---- FALTA ESTO
// No se puede entrar a un pasadizo desde su salida

// Entrar al primer salon tambien tarda 1 minuto !!!!!


int cant_salones, contador;
vector<tuple<int, int, int>> pasadizos;

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

void printVectorTuplas(vector<tuple<int, int, int>> &pasadizos){
    for(tuple<int, int, int> i : pasadizos){
        cout << "(" << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << ")" << endl;
    }
}

bool compareThirdElement(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    return get<2>(a) < get<2>(b);
}

void sortVectorOfTuplesByThirdElement(vector<tuple<int, int, int>>& tuples) {
    sort(tuples.begin(), tuples.end(), compareThirdElement);
}

int smallestThirdElement(vector<tuple<int, int, int>>& pasadizos) { //busca la arista en pasadizos con la menos cantidad de murallas que cubre
    int smallestIndex = 0;

    for (int i = 1; i < pasadizos.size(); i++) 
        if (get<2>(pasadizos[i]) < get<2>(pasadizos[smallestIndex])) 
            smallestIndex = i;

    return smallestIndex;
}

void medir(int inicio, int fin){    //se asegura de guardar en pasadizos solo los que cubran mayor cantidad de murallas hasta 3
    int cubre = fin - inicio;
    int smallestIndex = smallestThirdElement(pasadizos);

    if(pasadizos.size() < 3)
        pasadizos.push_back({inicio-1, fin-1, cubre});
    else{
        if(cubre >= get<2>(pasadizos[0]) || cubre >= get<2>(pasadizos[1]) || cubre >= get<2>(pasadizos[2])){
            get<0>(pasadizos[smallestIndex]) = inicio-1;
            get<1>(pasadizos[smallestIndex]) = fin-1;
            get<2>(pasadizos[smallestIndex]) = cubre;
        }
    }
}

bool esTunel(int u, int v){     //se fija si la arista vista es alguna de las que forman un pasadizo y cubren mayor cant. de murallas (lsa que se guardan en pasadizos)
    bool es_igual = false;

    if( (u == get<0>(pasadizos[0]) && v == get<1>(pasadizos[0])) ||
        (u == get<0>(pasadizos[1]) && v == get<1>(pasadizos[1])) ||
        (u == get<0>(pasadizos[2]) && v == get<1>(pasadizos[2])) ){
            es_igual = true;
        }
    return es_igual;
}

int distanciaMinima(vector<int> dist, vector<bool> spt){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < cant_salones; v++){
        if (spt[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }
 
    return min_index;
}

void dijkstra(vector<vector<int>> &grafo, int src){
    vector<int> dist(cant_salones, INT_MAX);    //dist guarda la distancia mas corta del origen hasta i
    vector<bool> spt(cant_salones, false);     //spt es true sii el nodo i esta incluido en shortest path tree o si ya se sabe la menor distancia del origen a i
 
    dist[src] = 0;
 
    for (int count = 0; count < cant_salones; count++) {
        int u = distanciaMinima(dist, spt);

        spt[u] = true;
        for (int v = 0; v < cant_salones; v++){
            if (!spt[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]){
                if(grafo[u][v] == 2 && esTunel(u, v))
                    dist[v] = dist[u] + grafo[u][v];
                else if (grafo[u][v] == 2)
                    continue;
                else
                    dist[v] = dist[u] + grafo[u][v];
            }
        }
    }
    //printVector(dist);
    cout << dist[dist.size()-1] + 1 << endl; // sumo 1 a la respuesta pq hay que considerar que entrar al primer salon (1er nodo) tambien tarda 1 min

}


int main(){
    int c, cant_tuneles;
    cin >> c;

    for(int i = 0; i < c; i++){
        contador = 0;
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
            medir(inicio, fin);

            grafo[inicio-1][fin-1] = 2;  // resto 1 en inicio y fin pq vectores empiezan con 0 y los casos de test empiezan en 1
                                         // le asigno 2 a la arista pq tarda 2 min en atravezar el tunel
        }

        sortVectorOfTuplesByThirdElement(pasadizos);
        //printVectorTuplas(pasadizos);
        //printMatrix(grafo);
        dijkstra(grafo, 0);
        
        pasadizos.clear();
    }

    return 0;
}
