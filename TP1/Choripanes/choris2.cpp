#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int cant_puestos;
int cant_proveedurias;  
int costo_minimo = INT_MAX;
vector<int> posiciones_puestos;


void printVector(vector<int> const &a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void ubicarProveedurias(int i, int cant_puestos, int cant_proveedurias, vector<int>& proveedurias_colocadas){

    if(i == cant_puestos){
        printVector(proveedurias_colocadas);
        return;
    }
    if(cant_proveedurias == 0)
        return;

    //pongo una proveeduria
    proveedurias_colocadas[i] = posiciones_puestos[i];
    ubicarProveedurias(i+1, cant_puestos, cant_proveedurias-1, proveedurias_colocadas);

    //no pongo una proveeduria
    proveedurias_colocadas[i] = 0;
    ubicarProveedurias(i+1, cant_puestos, cant_proveedurias, proveedurias_colocadas);

    return;
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
        
        vector<int> proveedurias_colocadas(cant_puestos, 0);
    
        //solucion
        ubicarProveedurias(0, cant_puestos, cant_proveedurias, proveedurias_colocadas);        

    }



    return 0;
}


/*
void recalcularProveeduriasCercanas(vector<int> posibles_ubicaciones){
    int ultima_proveeduria_vista;
    int prox_proveeduria;

    for(int i = 0; i < n; i++){
        //si hay una proveeeduria en mi puesto;
        if(posibles_ubicaciones[i] == posiciones_puestos[i]){
            // entonces la proveeduria mas cercana soy yo y soy la ultima proveeduria que vi
            proveeduria_mas_cercana[i] = posibles_ubicaciones[i];  
            ultima_proveeduria_vista = i;

        // si no hay una proveeduria en esta posicion    
        } else {

            //busco la proxima
            while(posiciones_puestos[i] != posibles_ubicaciones[i+1])
                i++;
            prox_proveeduria = i;

            // itero entre la ultima que vi y la proxima seteando la mas cercana de las del medio  
            for(int j = ultima_proveeduria_vista; j <= i; j++){
                if(abs(posiciones_puestos[j] - posibles_ubicaciones[ultima_proveeduria_vista]) > abs(posiciones_puestos[j] - posibles_ubicaciones[prox_proveeduria]))
                    proveeduria_mas_cercana[j] = posibles_ubicaciones[prox_proveeduria];
                else 
                    proveeduria_mas_cercana[j] = posibles_ubicaciones[ultima_proveeduria_vista];
            }

        }
    }
}

int calcularCosto(int i){
    int nuevo_costo;
    for(int j = 0; j < i; j++){
        nuevo_costo += abs(posiciones_puestos[j] - proveeduria_mas_cercana[j]);
    }
    return nuevo_costo;
}
*/
