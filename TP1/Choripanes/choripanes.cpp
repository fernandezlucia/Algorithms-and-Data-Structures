#include<algorithm>
#include<limits.h>
#include<iostream>
#include<vector>
using namespace std;

vector<int> puestos;
vector<vector<vector<int> > > memo;
vector<vector<vector<bool> > > decisiones;

vector<int> reconstruirSolucion(int kG, int n){
    int i = 1;
    int j = 0;
    int k = kG;
    vector<int> provedurias = vector<int>();

    while(i < n){
        if(decisiones[i][j][k]){
            provedurias.push_back(puestos[i]);
            j = i;
            k--;
        }
        i++;
    }
    return provedurias;
}

int calcularCosto(int j, int n){
    int acum = 0;
    for(int i = j; i < n; i++){
        int distanciaActual = abs(puestos[i]-puestos[j]);
        acum += distanciaActual;
    }
    return acum;
}


int calcularCosto2(int l, int r, int p){
    int acum = 0;
    for(int i = l; i <= r; ++i){
        int distanciaActual = abs(puestos[i]-puestos[p]);
        int distanciaNueva = abs(puestos[i]-puestos[r]);

        if(distanciaActual < distanciaNueva)
            acum += distanciaActual;
        else
            acum += distanciaNueva;
    }
    return acum;
}

int choris(int i, int j, int k, int n){
    if(k<0)
        return INT_MAX/2;
    if(i == n){
        if(k!=0)
            return INT_MAX/2;
        else
            return calcularCosto(j, n);
    }

    if(memo[i][j][k] != -1)
        return memo[i][j][k];
    
    int poner = choris(i+1, i, k-1, n) + calcularCosto2(j, i, j);
    int noPoner = choris(i+1, j, k, n);

    if(poner <= noPoner)
        decisiones[i][j][k] = 1;
    else
        decisiones[i][j][k] = 0;

    memo[i][j][k] = min(poner, noPoner);

    return memo[i][j][k];
}

int main() {

    int casos = 0;
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        int n, k;
        cin >> n;
        cin >> k;
        puestos = vector<int>();
        puestos.push_back(INT_MIN/2);
        for(int x = 0; x < n; x++){
            int val;
            cin >> val;
            puestos.push_back(val);
        }

        memo = vector<vector<vector<int> > >(n+2, vector<vector<int> >(n+2, vector<int>(k+2, -1)));
        decisiones = vector<vector<vector<bool> > >(n+2, vector<vector<bool> >(n+2, vector<bool>(k+2, false)));
        int costoMinimo = choris(1, 0, k, n+1);
        vector<int> provedurias = reconstruirSolucion(k, n+1);

        cout << costoMinimo << endl;

        for(int i = 0; i < provedurias.size(); i++){
            cout << provedurias[i] << " ";
        }
        cout << endl;

    }

    return 0;
}