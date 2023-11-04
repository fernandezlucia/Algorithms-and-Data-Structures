#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>

using namespace std;

// fortaleza: N salones divididos por murallas
// Escalar muralla   -> 1 min
// Recorrer pasadizo -> 2 min
// Maximos pasadizos que se pueden recorrer por caso: 3 
// No se puede ir hacia salones anteriores
// No se puede entrar a un pasadizo desde su salida
// Entrar al primer salon tambien tarda 1 minuto !

//Todo caso de test debe tener al menos 1 tunel

struct Tunel{
    int inicio;
    int fin;
    int cubren;
};

int cant_salones;
vector<Tunel> pasadizos;
vector<Tunel> tuneles;

void printVectorTuplas(vector<Tunel> &pasadizos){
    for(Tunel i : pasadizos){
        cout << "(" << i.inicio << ", " << i.fin << ", " << i.cubren << ")" << endl;
    }
}

bool compareThirdElement(const Tunel& a, const Tunel& b) {
    return a.cubren > b.cubren;
}

bool compareSecondElement(const Tunel& a, const Tunel& b) {
    return a.fin > b.fin;
}
void sortVectorOfTuplesByThirdElement(vector<Tunel>& tuples) {
    stable_sort(tuples.begin(), tuples.end(), compareThirdElement);
}

void sortVectorOfTuplesBySecondElement(vector<Tunel>& tuples) {
    stable_sort(tuples.begin(), tuples.end(), compareSecondElement);
}

bool esTunel(int u, int v, vector<Tunel>& tuneles){     //se fija si la arista vista es alguna de las que forman un pasadizo y cubren mayor cant. de murallas (lsa que se guardan en tuneles)
    bool es_igual = false;

    if(tuneles.size() != 0){
        if  (u == tuneles[0].inicio && v == tuneles[0].fin ||
             u == tuneles[1].inicio && v == tuneles[1].fin ||
             u == tuneles[2].inicio && v == tuneles[2].fin ){
                es_igual = true;
            }
    }

    return es_igual;
}

void getMax(vector<Tunel> &pasadizos, vector<Tunel> &tuneles){ // busca las tres tuneles que cubran mayor cant de murallas y no se pisen
    if (pasadizos.size() == 0)
        return;
    // ordenados de mayor a menor en cubrimiento
    tuneles.push_back(pasadizos[0]);
    int lastI = 0;
    for (int i = 1; i < pasadizos.size(); i++){
        if (pasadizos[i].inicio >= tuneles[0].fin || pasadizos[i].fin <= tuneles[0].inicio){
            tuneles.push_back(pasadizos[i]);
            lastI = i;
            break;
        }
    }

    for (int i = lastI; i < pasadizos.size(); i++){

        if(pasadizos[i].fin > tuneles[0].inicio && pasadizos[i].inicio < tuneles[0].fin)
            continue;
        
        if(pasadizos[i].inicio < tuneles[1].fin && pasadizos[i].inicio > tuneles[i].inicio)
            continue;
        
        tuneles.push_back(pasadizos[i]);
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

int dijkstra(vector<vector<int>> &grafo, int src, vector<Tunel>& tuneles){
    vector<int> dist(cant_salones, INT_MAX);    //dist guarda la distancia mas corta del origen hasta i
    vector<bool> spt(cant_salones, false);     //spt es true sii el nodo i esta incluido en shortest path tree o si ya se sabe la menor distancia del origen a i
 
    dist[src] = 0;

    for (int count = 0; count < cant_salones; count++) {
        int u = distanciaMinima(dist, spt);

        spt[u] = true;
        for (int v = 0; v < cant_salones; v++){
            if (!spt[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]){
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

        for(int k = 0; k < cant_salones-1; k++){
            grafo[k][k+1] = 1;  // cada nodo (salon) tiene una arista dirigida al siguiente nodo con peso 1 (pq tarda 1 min en saltar la muralla)
        }

        for(int j = 0; j < cant_tuneles; j++){
            int inicio, fin;
            cin >> inicio >> fin;
            grafo[inicio-1][fin-1] = 0;
            
            int cubre = fin - inicio;
            if(cubre > 2){
                pasadizos.push_back({inicio-1, fin-1, cubre});
            }
        }

        sortVectorOfTuplesByThirdElement(pasadizos);
        sortVectorOfTuplesBySecondElement(pasadizos);
        //printVectorTuplas(pasadizos);
        tuneles = vector<Tunel>();
        getMax(pasadizos, tuneles);
        for(Tunel t : tuneles){
            grafo[t.inicio][t.fin] = 2;
        }
        //cout << "--------------------" << endl;
        //printVectorTuplas(tuneles);
        int res1 = dijkstra(grafo, 0, tuneles);

        cout << res1 << endl;

        tuneles.clear();
        pasadizos.clear();
    }

    return 0;
}
