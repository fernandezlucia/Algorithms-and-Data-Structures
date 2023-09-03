#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

#define L 'L'
#define I 'I'
#define CROSS '+'
#define EMPTY '#'

typedef vector<vector<char>> Tablero;

int maxLen;
int minLen;
int n;
int m;

Tablero tablero;

enum Direccion {Arriba, Izquierda, Abajo, Derecha};

bool enRango(int i, int j){
    return (i < tablero.size() && i >= 0) && (j < tablero[0].size() && j >= 0);
}

void siguientePosicion(int prev_i, int prev_j, int direccion, int& sig_i, int& sig_j){
    sig_i = prev_i;
    sig_j = prev_j;
    
    switch(direccion){
        case Arriba:
            --sig_i;
            break;
        case Abajo:
            ++sig_i;
            break;
        case Derecha:
            ++sig_j;
            break;
        case Izquierda:
            --sig_j;
            break;
    }
}

void haySendero(vector<vector<bool> >& visitado, int i, int j, int direccion, int longitud){
    //caso base
    if(!enRango(i,j))
        return;

    if(visitado[i][j])
        return;

    if(tablero[tablero.size()-1][tablero[0].size()-1] == EMPTY)
        return;

    if(i == n - 1 && j == m - 1){
        minLen = min(minLen, longitud);
        maxLen = max(maxLen, longitud);
        return;
    }

    visitado[i][j] = true;
    
    int sig_i, sig_j, paridad;
    //caso recursivo
    switch(tablero[i][j]){
        case CROSS:
            for(int dir = Arriba; dir < 4; dir++){
                siguientePosicion(i, j, dir, sig_i, sig_j);
                haySendero(visitado, sig_i, sig_j, dir, longitud + 1);
            }
            break;
        
        case L:
            paridad = (direccion + 1) % 2;
            for(int dir = paridad; dir < 4; dir += 2){
                siguientePosicion(i, j, dir, sig_i, sig_j);
                haySendero(visitado, sig_i, sig_j, dir, longitud + 1);
            }
            break;
        
        case I:
            siguientePosicion(i, j, direccion, sig_i, sig_j);
            haySendero(visitado, sig_i, sig_j, direccion, longitud + 1);            
            break;
        
        case EMPTY:
            return;
        
        default:
            return;
    }

    visitado[i][j] = false;
}

//bool getInputFromFile(string file_path, vector<Tablero> &tableros) {
//    int c, n, m;
//    ifstream file (file_path);
//
//    if(!file.is_open()) {
//        return 0;
//    }
//
//    file >> c;
//
//    for(int i = 0; i < c; ++i) {
//        file >> n >> m;
//        Tablero current_table (n, vector<char> (m));
//
//        for(int j = 0; j < n; ++j){
//            string palabra;
//            file >> palabra;
//            for(int k = 0; k < palabra.size(); ++k){
//                current_table[j][k] = palabra[k];
//            }
//        }
//        
//        tableros.push_back(current_table);
//    }
//
//    file.close();
//
//    return 0;
//}
//
bool getInputManual(vector<Tablero> &tableros) {
    int c, n, m;
    char pieza;

    cin >> c;

    for(int i = 0; i < c; ++i) {
        cin >> n >> m;
        Tablero current_table (n, vector<char> (m));

        for(int j = 0; j < n; ++j){
            for(int k = 0; k < m; ++k){
                cin >> current_table[j][k];
            }
        }
        
        tableros.push_back(current_table);
    }
    
    return 0;
}

int main(int argc, char **argv) {
    vector<Tablero> tableros;
    bool failed_table_read;
    
    
    if(argc > 1)
        failed_table_read = 0;//getInputFromFile(argv[1], tableros);
    else
        failed_table_read = getInputManual(tableros);
    
    if(failed_table_read)
        return 1;

    //por cada test llenamos las estructuras

    for(int i = 0; i < tableros.size(); ++i){
        //backtracking
        int min, max;
        tablero = tableros[i];
        
        minLen = INT_MAX;
        maxLen = INT_MIN;

        n = tableros[i].size();
        m = tableros[i][0].size();

        vector<vector<bool>> visitado (n, vector<bool>(m, false));

        if(tablero[0][0] == I || tablero[0][0] == L){
            haySendero(visitado, 0, 0,  Abajo, 0);
        }
        haySendero(visitado, 0, 0,  Derecha, 0);

        if(minLen == INT_MAX && maxLen == INT_MIN)
            printf("IMPOSIBLE\n");
        else
            printf("POSIBLE %d %d\n", minLen, maxLen);
    }

    return 0;
}
