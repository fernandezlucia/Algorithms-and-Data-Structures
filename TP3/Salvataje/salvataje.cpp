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


int cant_salones;
vector<tuple<int, int, int>> pasadizos;
vector<tuple<int, int, int>> tuneles1;
vector<tuple<int, int, int>> tuneles2;


void printVectorTuplas(vector<tuple<int, int, int>> &pasadizos){
    for(tuple<int, int, int> i : pasadizos){
        cout << "(" << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << ")" << endl;
    }
}

bool compareThirdElement(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    return get<2>(a) > get<2>(b);
}

bool compareSecondElement(const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
    return get<1>(a) > get<1>(b);
}

void sortVectorOfTuplesByThirdElement(vector<tuple<int, int, int>>& tuples) {
    sort(tuples.begin(), tuples.end(), compareThirdElement);
}

void sortVectorOfTuplesBySecondElement(vector<tuple<int, int, int>>& tuples) {
    sort(tuples.begin(), tuples.end(), compareSecondElement);
}

bool esTunel(int u, int v, vector<tuple<int, int, int>>& tuneles){     //se fija si la arista vista es alguna de las que forman un pasadizo y cubren mayor cant. de murallas (lsa que se guardan en tuneles)
    bool es_igual = false;

    if(tuneles.size() != 0){
        if( (u == get<0>(tuneles[0]) && v == get<1>(tuneles[0])) ||
            (u == get<0>(tuneles[1]) && v == get<1>(tuneles[1])) ||
            (u == get<0>(tuneles[2]) && v == get<1>(tuneles[2])) ){
                es_igual = true;
            }
    }

    return es_igual;
}

void getMax(vector<tuple<int, int, int>>& pasadizos, vector<tuple<int, int, int>>& tuneles){ //busca las tres tuneles que cubran mayor cant de murallas y no se pisen
    if (pasadizos.size() != 0){

        tuneles.push_back(pasadizos[0]);
        pasadizos.erase(pasadizos.begin());
    

        for (int i = 0; i < pasadizos.size(); i++){
            if(get<0>(pasadizos[i]) >= get<1>(tuneles[0]) || get<1>(pasadizos[i]) <= get<0>(tuneles[0])){ 
                tuneles.push_back(pasadizos[i]);
                pasadizos.erase(pasadizos.begin());
                break;
            }
        } 

        for (int i = 0; i < pasadizos.size(); i++){
            if( (get<0>(pasadizos[i]) >= get<1>(tuneles[0]) || get<1>(pasadizos[i]) <= get<0>(tuneles[0]) ) &&
                (get<0>(pasadizos[i]) >= get<1>(tuneles[1]) || get<1>(pasadizos[i]) <= get<0>(tuneles[1]) ) ){
                tuneles.push_back(pasadizos[i]);
                pasadizos.erase(pasadizos.begin());
                break;
            }
        } 
    }
    
}

int distanciaMinima(vector<int> dist, vector<bool> spt){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < cant_salones; v++){
        if (spt[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }
 
    return min_index;
}

int dijkstra(vector<vector<int>> &grafo, int src, vector<tuple<int, int, int>>& tuneles){
    vector<int> dist(cant_salones, INT_MAX);    //dist guarda la distancia mas corta del origen hasta i
    vector<bool> spt(cant_salones, false);     //spt es true sii el nodo i esta incluido en shortest path tree o si ya se sabe la menor distancia del origen a i
 
    dist[src] = 0;
 
    for (int count = 0; count < cant_salones; count++) {
        int u = distanciaMinima(dist, spt);

        spt[u] = true;
        for (int v = 0; v < cant_salones; v++){
            if (!spt[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]){
                if(grafo[u][v] == 2 && esTunel(u, v, tuneles))
                    dist[v] = dist[u] + grafo[u][v];
                else if (grafo[u][v] == 2)
                    continue;
                else
                    dist[v] = dist[u] + grafo[u][v];
            }
        }
    }
    
    int res = dist[dist.size()-1] + 1;  // sumo 1 a la respuesta pq hay que considerar que entrar al primer salon (1er nodo) tambien tarda 1 min
    return res;
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
            int cubre = fin - inicio;
            
            pasadizos.push_back({inicio-1, fin-1, cubre});    
            grafo[inicio-1][fin-1] = 2;  // resto 1 en inicio y fin pq vectores empiezan con 0 y los casos de test empiezan en 1
                                         // le asigno 2 a la arista pq tarda 2 min en atravezar el tunel
        }

        sortVectorOfTuplesByThirdElement(pasadizos);
        getMax(pasadizos, tuneles1);
        int res1 = dijkstra(grafo, 0, tuneles1);

        sortVectorOfTuplesBySecondElement(pasadizos);
        sortVectorOfTuplesByThirdElement(pasadizos);
        getMax(pasadizos, tuneles2);

        int res2 = dijkstra(grafo, 0, tuneles2);
        
        if(res1 <= res2)
            cout << res1 << endl;
        else
            cout << res2 << endl;

        tuneles1.clear();
        tuneles2.clear();
        pasadizos.clear();
    }

    return 0;
}
