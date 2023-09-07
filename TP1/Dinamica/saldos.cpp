#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INDEFINIDO -1
int offset = 100000;
//i recorre el vector de xi
//saldoAcumulado la suma acumulada hasta el paso i

bool saldos(int i, int acumulado, int w, vector<int>& v, vector<vector<bool>>& memo, vector<pair<bool, bool>>& signos){
    if(i == 0)
        return acumulado == w;
    if(!memo[i][acumulado+offset]){
        bool sumar = saldos(i-1, acumulado+v[i-1], w, v, memo, signos);
        bool restar = saldos(i-1, acumulado-v[i-1], w, v, memo, signos);

        if(sumar)
            signos[i-1].first = true;
        
        if(restar)
            signos[i-1].second = true;
        
        memo[i][acumulado+offset] = sumar | restar;
    }
    cout << "asd" << endl;
    return memo[i][acumulado+offset];
}



int main() {


    /*size_t c, n, m = 0;
    cin >> c >> n >> m;*/
        
    size_t casos = 0;
    cin >> casos;
    
    for(int caso = 0; caso < casos; caso++){
        int n, w;
        cin >> n;
        cin >> w;
        vector<int> valores = vector<int>();
        for(int x = 0; x < n; x++){
            int val;
            cin >> val;
            valores.push_back(val);
        }
        vector<vector<bool>> memo = vector<vector<bool>>(n, vector<bool>(2*offset*n, NULL));
        vector<pair<bool, bool>> signos = vector<pair<bool, bool>>(n, make_pair(false, false));

        printf("%d", saldos(n, 0, w, valores, memo, signos));

        /*for(int i = 0; i < signos.size(); i++){
            if(signos[i].first and !signos[i].second)
                cout << "+";
            else if(!signos[i].first and signos[i].second)
                cout << "-";
            else
                cout << '?';
        }*/
    }

    return 0;
}


