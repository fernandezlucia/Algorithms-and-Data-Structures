#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>

using namespace std;

int llegue_a_paciente = 0;
int llegue_a_hospital = 0;
vector<vector<int>> esquina;
vector<vector<bool>> visitado;
vector<vector<int>> minutos;

#define HOSPITAL -1
#define PACIENTE -2

bool enRango(int i, int j){
    return (i >= 0 && i < esquina.size()) && (j >= 0 && j < esquina[0].size());
}

vector<pair<int, int>> esquinasAdyacentes(pair<int, int> e){
    int f = e.first;
    int c = e.second;
    vector<pair<int, int>> res(0);

    if(enRango(f+1, c))
        res.push_back({f+1, c});
    if(enRango(f, c+1))
        res.push_back({f, c+1});
    if(enRango(f-1, c))
        res.push_back({f-1, c});
    if(enRango(f, c-1))
        res.push_back({f, c-1});

    return res;
}

void BFS(pair<int, int> e, int num){
    queue<pair<int, int>> cola;
    visitado[e.first][e.second] = true;
    cola.push(e);

    while(!cola.empty()){
        pair<int, int> u = cola.front();
        cola.pop();

        vector<pair<int, int>> ady = esquinasAdyacentes(u);
        
        for(pair<int, int> a : ady){
            int f = a.first;
            int c = a.second;

            if(visitado[f][c])
                continue;

            //si llegue a la esquina del paciente la retorno
            if(esquina[f][c] == PACIENTE && llegue_a_paciente == 0){
                minutos[f][c] = minutos[u.first][u.second] + 1;
                llegue_a_paciente = minutos[u.first][u.second] + 1;
            }
            
            if(esquina[f][c] == HOSPITAL && llegue_a_hospital == 0){
                minutos[f][c] = minutos[u.first][u.second] + 1;
                llegue_a_hospital = minutos[u.first][u.second] + 1;
            }

            //si es distinto de cero, hay una manifestacion
            if(esquina[f][c] != 0 && esquina[f][c] <= minutos[u.first][u.second] + 1)
                continue;

            visitado[f][c] = true;
            minutos[f][c] = minutos[u.first][u.second] + 1;
            cola.push(a);
        }
    }
}

void reiniciarEstructuras(int filas, int columnas){
    visitado = vector<vector<bool>>(filas, (vector<bool>(columnas, 0)));
    minutos = vector<vector<int>>(filas, (vector<int>(columnas, 0)));
    esquina = vector<vector<int>>(filas, (vector<int>(columnas)));
    llegue_a_hospital = 0;    
    llegue_a_paciente = 0;
}

int main(){
    int cases;
    int filas;
    int columnas;
    pair<int, int> pos_hospital;
    pair<int, int> pos_paciente;

    cin >> cases;
    for(int i = 0; i < cases; i++){
        cin >> filas >> columnas;
        esquina = vector<vector<int>>(filas, (vector<int>(columnas)));
        for(int f = 0; f < filas; f++)
            for(int c = 0; c < columnas; c++)
                cin >> esquina[f][c];
    
        cin >> pos_hospital.first >> pos_hospital.second;
        cin >> pos_paciente.first >> pos_paciente.second;

        if(pos_hospital == pos_paciente){
            cout << "0 0"<< endl;
            reiniciarEstructuras(filas, columnas);
            continue;
        }

        esquina[pos_hospital.first][pos_hospital.second] = -1;
        esquina[pos_paciente.first][pos_paciente.second] = -2;

        visitado = vector<vector<bool>>(filas, (vector<bool>(columnas, 0)));
        minutos = vector<vector<int>>(filas, (vector<int>(columnas, 0)));

        BFS(pos_hospital, minutos[pos_paciente.first][pos_paciente.second]);
        visitado = vector<vector<bool>>(filas, (vector<bool>(columnas, 0)));
        BFS(pos_paciente, llegue_a_paciente);
        

        if(llegue_a_paciente*llegue_a_hospital == 0)
            cout << "IMPOSIBLE" << endl;
        else    
            cout << llegue_a_paciente << " " << llegue_a_hospital << endl; 

        reiniciarEstructuras(filas, columnas);
    }
    return 0;
}
