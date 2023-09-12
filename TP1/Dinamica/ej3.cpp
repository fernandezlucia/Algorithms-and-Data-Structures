#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INDEFINIDO -1

vector<int> saldos; //Vector xi enunciado
int saldoEsperado;
int n;
int max_acumulado_pos;

vector<vector<int>> memo(n, vector<int>(max_acumulado_pos*2, INDEFINIDO)); 
vector<char> vector_chars(n);

//i recorre el vector de xi
//saldoAcumulado la suma acumulada hasta el paso i

bool saldosPosibles(int i, int saldoAcumulado){

    bool hay_saldo_suma = false;
    bool hay_saldo_resta = false;
    //leimos todos los saldos
    //caso base
    if(i == n)
        return (saldoAcumulado == saldoEsperado);
        
    //caso recursivo
    if(saldoAcumulado > 0){
        if(memo[i][saldoAcumulado + max_acumulado_pos] != INDEFINIDO){
            cout << "Llega aca 1" << endl;
            return memo[i][saldoAcumulado];
        }
    }else{
        if(memo[i][-saldoAcumulado] != INDEFINIDO){
            return memo[i][saldoAcumulado];

        }
    }
    cout << "Llega aca 2" << endl;
    
    //si no esta definido, lo definimos
    hay_saldo_suma |= saldosPosibles(i+1, saldoAcumulado + saldos[i]);
    hay_saldo_resta |= saldosPosibles(i+1, saldoAcumulado - saldos[i]);

    if(saldoAcumulado > 0){
        memo[i][saldoAcumulado + max_acumulado_pos] = hay_saldo_suma || hay_saldo_resta;
    }else{
        memo[i][-saldoAcumulado] = hay_saldo_suma || hay_saldo_resta;
    }
    cout << "Llega aca 3" << endl;

    if(hay_saldo_suma && hay_saldo_resta){
        vector_chars[i] = '?';
    } else if(hay_saldo_suma){
        vector_chars[i] = '+';
    } else {
        vector_chars[i] = '-';
    }

    return hay_saldo_resta || hay_saldo_suma;
}



int main() {


    /*size_t c, n, m = 0;
    cin >> c >> n >> m;*/
        
    size_t N = 0;
    cin >> N ;
    n = N;
    max_acumulado_pos = n*10*10*10*10;
    
    cin >> saldoEsperado;

    for(int i = 0; i < n; i++){
        int elem;
        cin >> elem;
        saldos.push_back(elem);
    }
    
    //llamar a la funcion    
    saldosPosibles(0, 0);
    cout << "sale de saldos posibles" << endl;

    for(int i = 0; i < n; i++){
        cout << vector_chars[n - i - 1] << ", ";
    }

    return 0;
}


