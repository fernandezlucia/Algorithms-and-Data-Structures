#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int k = 3;  //provedurias
int n = 5;  //puestos
vector<int> posiciones_puestos = {1,5,15,20,30};
vector<int> proveeduria_mas_cercana;
int costo_minimo = INT_MAX;

void printVector(vector<int> const &a){
    for(int i = 0; i < a.size(); i++){
        int val = a[i]*posiciones_puestos[i];
        if(val == 0)
            continue;
        
        cout << val << " ";
    }
    cout << endl;
}





int ubicarProveedurias(vector<int>& posibles_ubicaciones, int i, int costo_acumulado){
    if(posibles_ubicaciones.size() == k){
        printVector(posibles_ubicaciones);
        return costo_acumulado;
    }

    if(costo_acumulado > costo_minimo)
        return INT_MAX;
    
    posibles_ubicaciones.push_back(posiciones_puestos[i]);
    costo_acumulado += calcularCosto(posibles_ubicaciones);
    int pongo_prov = ubicarProveedurias(posibles_ubicaciones, i+1, nuevo_costo);

    posibles_ubicaciones.pop_back();
    nuevo_costo = calcularCosto(posibles_ubicaciones);
    int no_pongo = ubicarProveedurias(posibles_ubicaciones, i+1, nuevo_costo);
    
    return min(pongo_prov, no_pongo);
}
























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

int ubicarProveedurias(vector<int>& posibles_ubicaciones,int cant_prov, int i, int costo){
    int costo_actual;
    int costo_anterior = costo;

    if(cant_prov > k)
        return INT_MAX;

    if(i == n){
        printVector(posibles_ubicaciones);
        return costo_minimo;
    }

    posibles_ubicaciones.push_back(posiciones_puestos[i]);

    costo_actual = calcularCosto(i);
    if(costo_actual >= costo_minimo)
        return INT_MAX;
    else
        costo_minimo = costo_actual;
    
    int pongo_prov = ubicarProveedurias(posibles_ubicaciones,cant_prov, i+1, costo_actual);
    recalcularProveeduriasCercanas(posibles_ubicaciones);

    posibles_ubicaciones.pop_back();
    int no_pongo = ubicarProveedurias(posibles_ubicaciones, cant_prov, i+1, costo_anterior);
    
    return min(pongo_prov, no_pongo);
}


int main(){
    //int casos = 0;
    //
    //cin >> casos;
    //
    //for(int caso = 0; caso < casos; caso++){
    //    cin >> cant_puestos >> cant_proveedurias;
    //    
    //    posiciones_puestos = {};
    //    
    //    for(int i = 0; i < cant_puestos; i++){
    //        int puesto_i;
    //        cin >> puesto_i;
    //        posiciones_puestos.push_back(puesto_i);
    //    }
//
//    //solucion
//
//    }

    vector<bool> posiblesUbicaciones;

    ubicarProveedurias(posiblesUbicaciones, 0, 0, 0);

    return 0;
}
