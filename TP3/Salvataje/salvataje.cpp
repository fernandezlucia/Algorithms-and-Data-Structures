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

void printVector(vector<vector<int>> &graph){
    for(vector<int> i : graph){
        cout << "(";
        for(int l = 0; l < i.size(); l++)
            cout << i[l] << " ";
        cout << ")" << endl;
    }
}

void printOnlyVector(vector<int> v){
    for(int i : v)
        cout << v[i] << " ";
    cout << endl;
}

int minDistance(vector<int> dist, vector<bool> sptSet){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < cant_salones; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void printSolution(vector<int> dist, int n){
    int N = dist.size();
    cout << dist[N-1] + 1 << endl; //RESPUESTA

}

//int graph[cant_salones][cant_salones]
void dijkstra(vector<vector<int>> &graph, int src){
    vector<int> dist(cant_salones, INT_MAX);
    vector<bool> sptSet(cant_salones, false);

    //for (int i = 0; i < cant_salones; i++)
    //    dist[i] = INT_MAX, sptSet[i] = false;
 
    dist[src] = 0;
 
    for (int count = 0; count < cant_salones - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;
        for (int v = 0; v < cant_salones; v++)
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    //printOnlyVector(dist);
    printSolution(dist, cant_salones);
}



int main(){
    int c, cant_tuneles;
    cin >> c;

    for(int i = 0; i < c; i++){
        cin >> cant_salones >> cant_tuneles;
        vector<vector<int>> graph(cant_salones, vector<int>(cant_salones,0));

        for(int k = 0; k < cant_salones; k++){
            if(k == cant_salones-1)
                continue;
            else
                graph[k][k+1] = 1;
            
        }


        for(int j = 0; j < cant_tuneles; j++){
            int inicio, fin;
            cin >> inicio >> fin;

            graph[inicio-1][fin-1] = 2;
        }


        //Devolver MINIMO TIEMPO POSIBLE EN LLEGAR A ULTIMO SALON
        //printVector(graph);
        dijkstra(graph, 0);
        
    }

    return 0;
}
