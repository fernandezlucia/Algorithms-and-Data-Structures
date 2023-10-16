#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <tuple>
#include <limits.h>

using namespace std;

const int inf = INT_MAX;

int edificios;
int cant_conexiones;
vector<vector<pair<int, int>>> matriz_ady;
vector<vector<int>> frontera;
vector<bool> en_frontera;

void printVectorOfVectors(const std::vector<std::vector<int>>& vec) {
    for (const std::vector<int>& innerVec : vec) {
        for (int element : innerVec) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
void agregarAFrontera(int v, vector<pair<int, int>> vencindario, vector<bool> visitado){
   for(int i = 0; i < edificios; ++i){
        if(matriz_ady[v][i].first != inf && !visitado[i]){
            frontera.push_back({v, i, matriz_ady[v][i].first, matriz_ady[v][i].second});
        }
   }
}

int maximoVecino(float& D, float& R){
    int d = frontera[0][2];
    int r = frontera[0][3];
    int v = 0;

    
    int res = 0;

    for(int i = 1; i < frontera.size(); ++i){      
        if((D + d)/(R + r) < (D + frontera[i][2])/(R + frontera[i][3])){
            d =  frontera[i][2];
            r =  frontera[i][3];
            v = i;
        }
    }

    D += frontera[v][2];
    R += frontera[v][3];

    cout << D << " " << R<< endl;
    res = frontera[v][1];
    frontera.erase(frontera.begin() + v);
    return res;
}

void prim(){
    vector<bool> visitado(edificios, false);
    int aristas_colocadas = 0;
    float D = 0;
    float R = 0; 


    agregarAFrontera(0, matriz_ady[0], visitado);      

    visitado[0] = true;
    while(frontera.size() != 0){
        int e = maximoVecino(D, R);
        if(!visitado[e]){
            visitado[e] = true;
            agregarAFrontera(e, matriz_ady[e], visitado);
            aristas_colocadas++;
        }
                printVectorOfVectors(frontera);
    }

    if(aristas_colocadas == edificios - 1)
        cout << D << " " << R << endl;
}


int main(){
    int casos;
    
    cin >> casos;

    for(int c = 0; c < casos; ++c){
        cin >> edificios >> cant_conexiones;

        matriz_ady =  vector<vector<pair<int, int>>>(edificios, vector<pair<int, int>>(cant_conexiones, {inf, inf}));
        frontera = vector<vector<int>>(0);
    en_frontera = vector<bool>(edificios, false);
        for(int i = 0; i < cant_conexiones; ++i){
            int e1, e2, d, r;
            cin >> e1 >> e2 >> d >> r;
            matriz_ady[e1-1][e2-1] = {d, r};
            matriz_ady[e2-1][e1-1] = {d, r};
        }
        prim();
    }


    return 0;
}