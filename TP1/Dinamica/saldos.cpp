#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INDEFINIDO -1
int offset = 10000;
//i recorre el vector de xi
//saldoAcumulado la suma acumulada hasta el paso i

bool saldos(int i, int acumulado, int w, vector<int>& v, vector<vector<bool>>& memo, vector<pair<bool, bool>>& signos){

    if(i == 0)
        return acumulado == w;
    if(memo[i][acumulado+offset] == NULL){
        bool sumar = saldos(i-1, acumulado+v[i-1], w, v, memo, signos);
        bool restar = saldos(i-1, acumulado-v[i-1], w, v, memo, signos);

        if(sumar)
            signos[i-1].first = true;
        
        if(restar)
            signos[i-1].second = true;
        
        memo[i][acumulado+offset] = sumar | restar;
    }
    return memo[i][acumulado+offset];
}



int main() {


    /*size_t c, n, m = 0;
    cin >> c >> n >> m;*/
        
    size_t casos = 0;
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        int n, w;
        cin >> n >> w;
        vector<int> v = vector<int>(n, 0);

        for(int x = 0; x < n; x++){
            cin >> v[x];
        }
        vector<vector<bool>> memo = vector<vector<bool>>(n, vector<bool>(2*offset*w, NULL));
        vector<pair<bool, bool>> signos = vector<pair<bool, bool>>(n, make_pair(false, false));
        saldos(n, 0, w, v, memo, signos);

        for(int i = 0; i < signos.size(); i++){
            if(signos[i].first and !signos[i].second)
                cout << "+";
            else if(!signos[i].first and signos[i].second)
                cout << "-";
            else
                cout << '?';
        }
    }

    return 0;
}


