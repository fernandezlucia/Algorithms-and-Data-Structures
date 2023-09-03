#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>

using namespace std;

long long norm = 1000000007;

struct Par{
    long long Mi;
    long long Ci;
};

bool comparar(const Par& a, const Par& b){
    long double res1 = (long double)a.Ci / (long double)a.Mi;
    long double res2 = (long double)b.Ci / (long double)b.Mi;
    return res1 > res2;
};


long greedy(vector<long long> M, vector<long long> C, int n){
    //Estrategia greedy: ordenar los parciales según la razón Ci / Mi (descontento generado por minuto) de mayor a menor entrega solución óptima
    //pues minimiza la suma acumulada de tiempo esperado para el alumno de mayor descontento por minuto de los que aún no corrigó.

    //Inicializamos vector de pares Ci, Mi sobre el que vamos a ordenar según el coeficiente.
    vector<Par> pares = vector<Par>(n);
    for(int i = 0; i < n; i++){
        pares[i].Mi = M[i];
        pares[i].Ci = C[i];
    }

    //Utilizamos stable sort para asegurar complejidad a lo sumo n*log^2(n) -sort no garantiza complejidad de peor caso, solo de caso promedio-
    stable_sort(pares.begin(), pares.end(), comparar);
    
    //Una vez ordenado, basta con acumular la suma de tiempo esperado multiplicado al descontento para cada alumno en el orden que tocó.
    long long minutos = 0;
    long long acum = 0;
    for(int i = 0; i < n; i++){
        minutos += pares[i].Mi;
        acum = (acum + minutos * pares[i].Ci) % norm;
    }

    return acum;
}

/*
bool getInputFromFile(string file_path, vector<long long> M, vector<long long> C){
    int c, n, M_i, C_i;
    ifstream file (file_path);

    if(!file.is_open()) {
        return 0;
    }

    file >> c;

    for(int j = 0; j < c; j++){
        file >> n;
        for (int i = 0; i < n; i++){
            file >> M_i;
            M.push_back(M_i);
        }

        for (int i = 0; i < n; i++){
            file >> C_i;
            C.push_back(C_i);
        }
    
        //printVector(M);
        //printVector(C);

        cout << greedy(M, C, n) << endl;
        M.clear();
        C.clear();
    }

    file.close();

    return 0;
}
*/

bool getInputManual(vector<long long> M, vector<long long> C){
    int c, n, M_i, C_i;
    cin >> c;

    for(int j = 0; j < c; j++){
        cin >> n;
        for (int i = 0; i < n; i++){
            cin >> M_i;
            M.push_back(M_i);
        }

        for (int i = 0; i < n; i++){
            cin >> C_i;
            C.push_back(C_i);
        }
    
        //printVector(M);
        //printVector(C);

        cout << greedy(M, C, n) << endl;
        M.clear();
        C.clear();
    }

    return 0;
}


int main(int argc, char **argv) {
    bool failed_table_read;
    vector<long long> M;
    vector<long long> C;
    
    if(argc > 1)
        failed_table_read = 0; //getInputFromFile(argv[1], M, C);
    else
        failed_table_read = getInputManual(M, C);
    
    if(failed_table_read)
        return 1;

    return 0;
}
