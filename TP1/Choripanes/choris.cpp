#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int cant_puestos;
int cant_proveedurias;  
int costo_minimo = INT_MAX;
vector<int> posiciones_puestos;
vector<vector<int>> memo;

#define INDEFINIDO -1

void printVector(vector<int> const &a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int ubicarProveedurias(int n, int k, vector<int>& proveedurias_colocadas, vector<vector<int>> memo){
    int costo_poner_prov, costo_no_poner_prov;
    
    if(k == 0){
        if(n == 0){
            return costo_minimo;
        }
        else
            return INT_MAX;
    }
    
    if(n == 0)
        return INT_MAX;

    if(memo[n][k] != INDEFINIDO)
        return memo[n][k];
    

    proveedurias_colocadas[cant_puestos-n-1] = posiciones_puestos[cant_puestos-n-1];
    costo_poner_prov = ubicarProveedurias(n-1, k-1, proveedurias_colocadas, memo);
    
    proveedurias_colocadas[cant_puestos-n-1] = 0;
    costo_no_poner_prov = ubicarProveedurias(n-1, k, proveedurias_colocadas, memo);
    printVector(proveedurias_colocadas);

    if(costo_poner_prov < costo_minimo || costo_no_poner_prov < costo_minimo)
        costo_minimo = min(costo_poner_prov, costo_no_poner_prov);

    memo[n][k] = costo_minimo;
    return costo_minimo;
}


int main(){
    int casos = 0;
    
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        cin >> cant_puestos >> cant_proveedurias;

        posiciones_puestos = vector<int>();
        
        for(int i = 0; i < cant_proveedurias; i++){
            int puesto_i;
            cin >> puesto_i;
            posiciones_puestos.push_back(puesto_i);
        }
        
        vector<int> proveedurias_colocadas(cant_proveedurias, 0);
        vector<vector<int>> memo(cant_puestos, vector<int>(cant_proveedurias, INDEFINIDO));
    
        //solucion
        ubicarProveedurias(cant_puestos-1, cant_proveedurias-1, proveedurias_colocadas, memo);        

    }



    return 0;
}


void ubicarProveedurias(vector<int> posibles_ubicaciones, int i, int cant_prov, int cant_vacio){
   
    if(cant_prov > k || cant_vacio > (n - k))
        return;
    
    //caso base 
    if(i == n){
        printVector(posibles_ubicaciones);
        return;
    }
    
    //ponemos una proveeduria en la posicion i
    posibles_ubicaciones[i] = posiciones_puestos[i];
    ubicarProveedurias(posibles_ubicaciones, i+1, cant_prov + 1, cant_vacio);

    //no la ponemos
    posibles_ubicaciones[i] = 0;
    ubicarProveedurias(posibles_ubicaciones, i+1, cant_prov, cant_vacio + 1);
    
    return;
}