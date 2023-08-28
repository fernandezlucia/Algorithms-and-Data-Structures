#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Tablero;

vector<int> longitudes;

enum Formas {UpRight, UpLeft, DownLeft, DownRight, Vertical, Horizontal, Cross, Empty};



bool esSenderoValido(Tablero& tablero, int& longitud){
    int camino = 0;
    longitud = camino;
    return true;
}

void printT(Tablero& tablero){
    for(int i = 0; i < tablero.size(); i ++){
        for(int j = 0; j < tablero[i].size(); j++){
            cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }
}

bool haySendero(Tablero& tablero, int i, int j){

    int n = tablero.size(), m = tablero[0].size();
    //estoy en el ultimo casillero (caso base)
    if(i == n-1 && j == m-1){
        printT(tablero);
        return true;
    }
    
    int rotaciones = 0;
    switch(tablero[i][j]){
        case UpRight:
            rotaciones = 3;
            break;
        case Vertical:
            rotaciones = 1;
            break;
        default:
            rotaciones = 0;
            break;
    }

    int sig_i = j < m ? i : i+1;
    int sig_j = j < m ? j + 1 : 0;
    int aux = tablero[i][j];
    bool acum = true;
    for(int k = 0; k <= rotaciones; k++){
        cout << "recursivo i j k val rotaciones " << i << " " << j << " " << k << " " << tablero[i][j] << " " << rotaciones << endl;
        tablero[i][j] += 1;
        acum =+ haySendero(tablero, sig_i, sig_j);
    }
    tablero[i][j] = aux;
    return acum;
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

    
    if(argc > 1)
        failed_table_read = getInputFromFile(argv[1], tableros);
    else
        failed_table_read = getInputManual(tableros);
    
    if(failed_table_read)
        return EXIT_FAILURE;

    //por cada test llenamos las estructuras

    for(int i = 0; i < tableros.size(); ++i){
        //backtracking
        haySendero(tableros[i], 0, 0);
    }

    return EXIT_SUCCESS;
}