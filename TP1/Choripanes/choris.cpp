#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int k = 3;  //provedurias
int n = 5;  //puestos
vector<int> posiciones_puestos;
vector<int> proveeduria_mas_cercana;
int costo_minimo = INT_MAX;

void printVector(vector<int> const &a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void recalcularProveeduriasCercanas(vector<int> posibles_ubicaciones){
    int ultima_proveeduria_vista;
    int prox_proveeduria;

    for(int i = 0; i < n; i++){
        //si hay una proveeeduria en mi puesto;
        if(posiciones_puestos[i] == posibles_ubicaciones.back()){
            for(int j = i; j < n; j++)
                proveeduria_mas_cercana[j] = posibles_ubicaciones.back();
            break;
            
        }else if(posibles_ubicaciones[i] == posiciones_puestos[i]){
            // entonces la proveeduria mas cercana soy yo y soy la ultima proveeduria que vi
            proveeduria_mas_cercana[i] = posibles_ubicaciones[i];  
            ultima_proveeduria_vista = i;

            // si no hay una proveeduria en esta posicion    
        } else {
                //busco la proxima
            while(posiciones_puestos[i] && posibles_ubicaciones[i+1] && posiciones_puestos[i] != posibles_ubicaciones[i+1])
                i++;
            prox_proveeduria = i;
            // itero entre la ultima que vi y la proxima seteando la mas cercana de las del medio  
            for(int j = ultima_proveeduria_vista; j <= i; j++){
                if(abs(posiciones_puestos[j] - posibles_ubicaciones[ultima_proveeduria_vista]) > abs(posiciones_puestos[j] - posibles_ubicaciones[prox_proveeduria]))
                    proveeduria_mas_cercana[j] = posibles_ubicaciones[prox_proveeduria];
                else 
                    proveeduria_mas_cercana[j] = posibles_ubicaciones[ultima_proveeduria_vista];
            }
            ultima_proveeduria_vista = prox_proveeduria;
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

int ubicarProveedurias(vector<int>& posibles_ubicaciones, int cant_prov, int i, int costo){
    int costo_actual;
    int costo_anterior = costo;

    if(cant_prov > k)
        return INT_MAX;

    if(i == n){
        printVector(posibles_ubicaciones);
        return costo_minimo;
    }

    posibles_ubicaciones.push_back(posiciones_puestos[i]);
    //cout << cant_prov << " " << i << " " << costo << endl;
    recalcularProveeduriasCercanas(posibles_ubicaciones);

    costo_actual = calcularCosto(i);
    if(costo_actual >= costo_minimo)
        return INT_MAX;
    else
        costo_minimo = costo_actual;


    int pongo_prov = ubicarProveedurias(posibles_ubicaciones, cant_prov+1, i+1, costo_actual);


    posibles_ubicaciones.pop_back();
    int no_pongo = ubicarProveedurias(posibles_ubicaciones, cant_prov, i+1, costo_anterior);
    
    return min(pongo_prov, no_pongo);
}


int main(){
    int casos = 0;
    
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        cin >> n >> k;

        posiciones_puestos = vector<int>();
        
        for(int i = 0; i < n; i++){
            int puesto_i;
            cin >> puesto_i;
            posiciones_puestos.push_back(puesto_i);
        }

    //solucion
        vector<int> posibles_ubicaciones = {};
        ubicarProveedurias(posibles_ubicaciones, 0, 0, 0);
                

    }



    return 0;
}
