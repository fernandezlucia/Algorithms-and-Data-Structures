#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;

typedef vector<vector<int>> Tablero;

vector<int> longitudes;
int cantPiezas = 7;
enum Formas {UpRight, UpLeft, DownLeft, DownRight, Vertical, Horizontal, Cross, Empty};
vector<int> direccionesX = {-1, 1, 0, 0};
vector<int> direccionesY = {0, 0, -1, 1};

int minLen;
int maxLen;
int n,m;

bool haySendero(Tablero& tablero, int i, int j, int longitud, Tablero visitados){
    int aux = tablero[i][j];
    int rotaciones = 0;

    // caso base
    if(i == n-1 && j == m-1){
        minLen = min(longitud, minLen);
        maxLen = max(longitud, maxLen);
        return true;
    }

    visitados[i][j] = true;
    int piezaOriginal = tablero[i][j];

    for(int k = 0; k < 4; k++){

        int sig_i = i + direccionesX[k];
        int sig_j = j + direccionesY[k];

        bool direccionValida = sig_i < n && sig_j < m && !visitados[sig_i][sig_j];

        if(direccionValida){
            int piezaActual = tablero[sig_i][sig_j];
            if(piezaActual == Empty)
                return false;

            if(piezaActual == Cross)
                return haySendero(tablero, sig_i, sig_j, longitud+1, visitados);
            else if(piezaActual == Vertical){
                //chequeo compatibilidad entre piezas
                
            }
            else if()

        }

    }


    
 }


/*
    Indexar recibe un char y lo traduce al número correspondiente.
    De este modo el dominio pasa de caracteres a números, y podemos encontrar maneras de representar todos los ángulos de rotación.
*/

int indexar(char c){
    switch(c){
        case 'L':
            return UpRight;
        case '+':
            return Cross;
        case '#':
            return Empty;
        case 'I':
            return Vertical;
    }
}


bool getInputFromFile(string file_path, vector<Tablero> &tableros) {
    int c, n, m;
    ifstream file (file_path);

    if(!file.is_open()) {
        return EXIT_FAILURE;
    }

    file >> c;

    for(int i = 0; i < c; ++i) {
        file >> n >> m;
        Tablero current_table (n, vector<int> (m));

        for(int j = 0; j < n; ++j){
            for(int k = 0; k < m; ++k){
                char temp;
                file >> temp;
                current_table[j][k] = indexar(temp);
            }
        }
        
        tableros.push_back(current_table);
    }

    file.close();

    return EXIT_SUCCESS;
}

bool getInputManual(vector<Tablero> &tableros) {
    int c, n, m;
    char pieza;

    cin >> c;

    for(int i = 0; i < c; ++i) {
        cin >> n >> m;
        Tablero current_table (n, vector<int> (m));

        for(int j = 0; j < n; ++j){
            for(int k = 0; k < m; ++k){
                char temp;
                cin >> temp;
                current_table[j][k] = indexar(temp);
            }
        }
        
        tableros.push_back(current_table);
    }
    
    return EXIT_SUCCESS;
}


int main(int argc, char **argv) {
    vector<Tablero> tableros;
    bool failed_table_read;
    longitudes = vector<int>();
    
    if(argc > 1)
        failed_table_read = getInputFromFile(argv[1], tableros);
    else
        failed_table_read = getInputManual(tableros);
    
    if(failed_table_read)
        return EXIT_FAILURE;

    //por cada test llenamos las estructuras


    for(int i = 0; i < tableros.size(); ++i){
        //backtracking

        minLen = INT_MAX;
        maxLen = -INT_MAX;

        n = tableros[i].size();
        m = tableros[i][0].size();

        Tablero visitados = vector<vector<int>>(n, vector<int>(m, 0));
        if(haySendero(tableros[i], 0, 0, 0, visitados))
            printf("POSIBLE {%d} {%d}", minLen, maxLen);
        
    }

    return EXIT_SUCCESS;
}