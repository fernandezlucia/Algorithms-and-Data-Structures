#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define UNDEFINED -1

int n, m;
int companeros;
vector<vector<int>> mapa;

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

void printVectorpair(vector<pair<int, int>> &v){
    for(pair<int,int> i : v){
        cout << "(" << i.first << ", " << i.second  << ")" << endl;
    }
}

void printVector(vector<int> &v){
    for (int i : v)
        cout << i << " ";
    cout << endl;
}


vector<pair<int, int>> caminoAumento(vector<vector<int>>& red_residual, vector<pair<int, int>>& camino){
    vector<bool> visitado(n, false);
    visitado[0] = true;
    queue<int> queue;
    queue.push(0);

    while(!queue.empty()){
        int v = queue.front();
        queue.pop();

        for(int u = 0; u < red_residual[v].size(); u++){
            if(red_residual[v][u] == UNDEFINED)
                continue;
            
            if(u == n-1){
                camino.push_back({v, u});
                return camino;
            }

            int cant_hijos = 0;
            for(int h = 0; h < red_residual[u].size(); h++){
                if(mapa[u][h] != UNDEFINED)
                    cant_hijos++;
            }
            
            if(cant_hijos == 0 )
                continue;
            
            if(!visitado[u]){
                visitado[u] = true;
                queue.push(u);
                camino.push_back({v, u});
                break;
            }
        }
    }
    return camino;
}

int minAristaenCamino(vector<pair<int, int>>& camino, vector<vector<int>>& red_residual){
    int min = red_residual[camino[0].first][camino[0].second];
    for(int i = 1; i < camino.size(); i++){
        if(red_residual[camino[i].first][camino[i].second] < min)
            min = red_residual[camino[i].first][camino[i].second];
    }
    return min;
}

int flujoMaximo(vector<vector<int>>& red_residual, vector<vector<int>> flujo){
    vector<pair<int, int>> camino;
    int flujo_max = 0;
    while(caminoAumento(red_residual, camino).size() > 0){
        printVectorpair(camino);
        
        int min_arista = minAristaenCamino(camino,red_residual);
        flujo_max += min_arista;

        //cout << "---------" << endl;
        for(int a = 0; a < camino.size(); a++){
            int i = camino[a].first;
            int j = camino[a].second;

            if(mapa[i][j] != UNDEFINED){    // si esta definido ij en el grafo
                if(flujo[i][j] + min_arista == mapa[i][j]){     // si sumandole el minimo llena la capacidad de la arista
                    flujo[i][j] += min_arista;  // suma el flujo en el grafo
                    red_residual[j][i] = mapa[i][j];    //actualiza la red dando vuelta la arista
                    red_residual[i][j] = UNDEFINED;
                } else if(flujo[i][j] + min_arista < mapa[i][j]){   //si sumandole el minimo no llena la capacidad de la arista y es mayor a 0
                    flujo[i][j] += min_arista;  // suma el flujo en el grafo
                    red_residual[i][j] -= min_arista;   // actualiza la red poniendo la arista que ya estaba con el valor de flujo que todavia puede pasar por esa arista
                    red_residual[j][i] = min_arista;    // agrega otra arista en la red q va al reves con el flujo que ya paso por esa arista
                }   
            } else if(mapa[j][i] != UNDEFINED){
                flujo[j][i] -= min_arista;
                red_residual[i][j] = mapa[j][i];   
                red_residual[j][i] = UNDEFINED;
            }

        }
        //cout << "min: " << min_arista << endl;
        cout << "---------" << endl;
        camino.clear();
    }
    return flujo_max;
}

int main(){
    int c;

    cin >> c;

    for (int i = 0; i < c; i++){
        cin >> n >> m >> companeros;
        mapa = vector<vector<int>> (n, vector<int>(m, UNDEFINED));
        vector<vector<int>> red_residual(n, vector<int>(m, UNDEFINED));
        vector<vector<int>> flujo(n, (vector<int>(m, 0)));
        //flujo inicial cero ??
        // ij ∈ AR si xij < uij 
        // ji ∈ AR si xij > 0.
        for(int j = 0; j < m; j++){
            int esq1, esq2, cant_herramientas;
            cin >> esq1 >> esq2 >> cant_herramientas;
            mapa[esq1-1][esq2-1] = cant_herramientas;
            red_residual[esq1-1][esq2-1] = cant_herramientas;
        }

        //printMatrix(red_residual);
        int flujo_max = flujoMaximo(red_residual, flujo);
        cout << flujo_max << endl;
              
    }

    return 0;
}