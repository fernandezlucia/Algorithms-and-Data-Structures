#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>
#include <queue>

using namespace std;

// fortaleza: N salones divididos por murallas
// Escalar muralla   -> 1 min
// Recorrer pasadizo -> 2 min
// Maximos pasadizos que se pueden recorrer por caso: 3 
// No se puede ir hacia salones anteriores
// No se puede entrar a un pasadizo desde su salida
// Entrar al primer salon tambien tarda 1 minuto !

//Todo caso de test debe tener al menos 1 tunel


struct Arista{
    int w;
    int d;
};

int cant_salones;
vector<vector<Arista>> grafo;

/*void printVectorTuplas(vector<Tunel> &pasadizos){
    for(Tunel i : pasadizos){
        cout << "(" << i.inicio << ", " << i.fin << ", " << i.cubren << ")" << endl;
    }
}*/

int dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int,int>>> pq;
    vector<int> dist(cant_salones*4, INT_MAX);

    pq.push({0, src});
    
    dist[src] = 0;
    
    while(!pq.empty()) {
        int we, dst;
        tie(we, dst) = pq.top();
        pq.pop();
        
        for(Arista e : grafo[dst]){
            if(dist[e.d] > dist[dst] + e.w){
                dist[e.d] = dist[dst] + e.w;
                pq.push({dist[e.d], e.d});
            }
        }
    }

    vector<int> capas;
    for(int k = 0; k <= 3; k++){
        //printf("pusheo posicion: %d con valor: %d \n", (cant_salones-1)+(cant_salones*k), dist[(cant_salones-1)+(cant_salones*k)]);
        capas.push_back(dist[(cant_salones-1)+(cant_salones*k)]);
    }

    return *min_element(capas.begin(), capas.end());
}


int main(){
    int c, cant_tuneles;
    cin >> c;

    for(int i = 0; i < c; i++){
        cin >> cant_salones >> cant_tuneles;
        grafo = vector<vector<Arista>>(cant_salones*4);
        
        for(int j = 0; j < cant_tuneles; j++){
            int inicio, destino;
            cin >> inicio >> destino;
            inicio--; destino--;
            for(int k = 0; k <= 2; k++){
                grafo[inicio+(cant_salones*k)].push_back({2, destino+(cant_salones*(k+1))});
            };
        }

        for(int j = 0; j < cant_salones*4; j++){
            if(j % cant_salones == cant_salones-1)
                continue;

            grafo[j].push_back({1, j+1});
            
        }
        
        int res1 = dijkstra(0);
        cout << res1+1 << endl;
        
    }

    return 0;
}
