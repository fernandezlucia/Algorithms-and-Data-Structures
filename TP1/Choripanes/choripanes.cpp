#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int proveedurias_target; 
int cant_puestos; 
int costo_minimo = INT_MAX;
vector<int> posiciones_puestos;
vector<int> proveeduria_mas_cercana;

void printVector(vector<int> const &a){
    for(int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}


void recalcularProveeduriasCercanas(vector<int> const &proveedurias_colocadas, int index_ultima_prov, int index_prov_actual){
    int proveeduria_anterior = proveedurias_colocadas[index_ultima_prov]; 
    int proveeduria_actual = proveedurias_colocadas[index_prov_actual]; 
    
    for(int i = index_ultima_prov + 1; i <= index_prov_actual; i++){
        if(abs(proveeduria_anterior - posiciones_puestos[i]) < abs(proveeduria_actual - posiciones_puestos[i]))
            proveeduria_mas_cercana[i] = proveeduria_anterior;
        else
            proveeduria_mas_cercana[i] = proveeduria_actual;

    }
    cout << "---" << endl;
    printVector(proveedurias_colocadas);

    printVector(proveeduria_mas_cercana);
}

    //(1, 5, 15, 20, 30)
    //(1, 0, 15, 0, 30)
    //(0, 0, 15, 20, 30)
    //(1, 5, 15, 0, 0)


int calcularCosto(int prov_anterior, int prov_actual){
    int nuevo_costo = 0;
    for(int j = prov_anterior + 1; j <= prov_actual; j++){
        nuevo_costo += abs(posiciones_puestos[j] - proveeduria_mas_cercana[j]);
    }

    return nuevo_costo;
}


int colocarProveedurias(vector<int>& proveedurias_colocadas, int index, int proveedurias_actuales, int ultima_prov, int costo_actual){
   // printVector(proveedurias_colocadas);
    int costo_poner_prov, costo_no_poner_prov;
   // cout << index << " " << proveedurias_actuales << " " << ultima_prov << " " << costo_actual << endl;
    if(proveedurias_actuales == proveedurias_target){
        //cout << "---" << endl;
        //printVector(proveedurias_colocadas);
        //cout << "---" << endl;
        return costo_minimo;
    }

    //caso base 
    if(index == posiciones_puestos.size()){
        return INT_MAX;
    }
    
    //ponemos una proveeduria en la posicion i
    proveedurias_colocadas[index] = posiciones_puestos[index];

    //recalculo las mas cercanas
    recalcularProveeduriasCercanas(proveedurias_colocadas, ultima_prov, index);
    
    //actualizo el costo
    //cout << calcularCosto(ultima_prov, index)  << "a" << endl;
    //if((costo_actual += calcularCosto(ultima_prov, index)) > costo_minimo)
    //    return INT_MAX;
    //else    
    //    costo_minimo = costo_actual;

    //hago el siguiente llamado dado que la puse
    costo_poner_prov = colocarProveedurias(proveedurias_colocadas, index+1, proveedurias_actuales + 1, index, costo_actual);

    //no la ponemos
    proveedurias_colocadas[index] = 0;
    costo_no_poner_prov = colocarProveedurias(proveedurias_colocadas, index+1, proveedurias_actuales, ultima_prov, costo_actual);

    return min(costo_poner_prov, costo_no_poner_prov);
}

int main(){
    int casos = 0;
    
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        cin >> cant_puestos >> proveedurias_target;
        
        posiciones_puestos = vector<int>();
        
        for(int i = 0; i < cant_puestos; i++){
            int puesto_i;
            cin >> puesto_i;
            posiciones_puestos.push_back(puesto_i);
        }

        //solucion   (1,5,15,20) (1,5,30)
        vector<int> aux(cant_puestos, 0);
        proveeduria_mas_cercana = aux;
        vector<int> proveedurias_colocadas(cant_puestos, 0);
        colocarProveedurias(proveedurias_colocadas, 0, 0, -1, 0);

    }

    return 0;
}
