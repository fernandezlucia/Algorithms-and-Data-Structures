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
    int index_prim_prov = 0;
    int index_ult_prov = proveedurias_colocadas.size();

    if(proveeduria_anterior == 0)
        proveeduria_anterior = proveeduria_actual;

    while(proveedurias_colocadas[index_prim_prov] == 0)
        index_prim_prov++;

    while(proveedurias_colocadas[index_ult_prov] == 0)
        index_ult_prov--;

    for(int i = 0; i <= index_prim_prov; i++)//deberia ser menor estricto?
        proveeduria_mas_cercana[i] = posiciones_puestos[index_prim_prov];

    for(int i = index_ult_prov; i < cant_puestos; i++)
        proveeduria_mas_cercana[i] = posiciones_puestos[index_ult_prov];
    
    
    for(int i = index_ultima_prov; i <= index_prov_actual; i++){
        if(abs(posiciones_puestos[i] - proveeduria_anterior) < abs(posiciones_puestos[i] - proveeduria_actual)){
            proveeduria_mas_cercana[i] = proveeduria_anterior;
        } else {
            proveeduria_mas_cercana[i] = proveeduria_actual;
        }
    }
}

int calcularCosto(){
    int nuevo_costo = 0;
    for(int j = 0; j <posiciones_puestos.size(); j++)
        nuevo_costo += abs(posiciones_puestos[j] - proveeduria_mas_cercana[j]);

    return nuevo_costo;
}


int colocarProveedurias(vector<int>& proveedurias_colocadas, int index, int proveedurias_actuales, int ultima_prov, int costo_parcial){
    int costo_poner_prov, costo_no_poner_prov, costo_actual;

    if(proveedurias_actuales == proveedurias_target){
        cout << costo_minimo << endl;
        printVector(proveedurias_colocadas);
        return costo_minimo;
    }

    //caso base 
    if(index == posiciones_puestos.size())
        return INT_MAX;
    
    proveedurias_colocadas[index] = posiciones_puestos[index];  //ponemos una proveeduria en la posicion i
    recalcularProveeduriasCercanas(proveedurias_colocadas, ultima_prov, index); //recalculo las mas cercanas

    costo_actual = calcularCosto();     //actualizo el costo    QUE PASA CON EL COSTO QUE VENGO ARRASTRANDO
    if(costo_actual < costo_minimo)
        costo_minimo = costo_actual;
    else    
        return INT_MAX; 

    //hago el siguiente llamado dado que la puse
    costo_poner_prov = colocarProveedurias(proveedurias_colocadas, index+1, proveedurias_actuales + 1, index, costo_parcial);

    //no la ponemos
    proveedurias_colocadas[index] = 0;
    costo_no_poner_prov = colocarProveedurias(proveedurias_colocadas, index+1, proveedurias_actuales, ultima_prov, costo_parcial);

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
        colocarProveedurias(proveedurias_colocadas, 0, 0, 0, 0);

    }

    return 0;
}
